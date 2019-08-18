#include "memory.hpp"
#include "KayosBoyUtils.hpp"

Memory::Memory(char* const pathToBootRom, Cartridge& cart) :
	mCartridge(cart)
{
	mVRam = new std::vector<uint8_t>(0x2000);
	mStaticWRam.resize(0x1000);
	mBankWRam = new std::vector<uint8_t>(0x1000);
	mOAM.resize(0x00A0);
	mUnused.resize(0x0060);
	mIORegisters.resize(0x0080);
	mHRAM.resize(0x007F); // Last byte is for the interrupt register

	LoadBootROM(pathToBootRom);
}

bool Memory::LoadBootROM(char* const path)
{
	uint8_t* bootRom = nullptr;
	size_t bootRomSize = LoadBinaryFile(path, &bootRom);

	bool ret = bootRomSize != 0;

	if (ret)
	{
		mBootRom = std::vector<uint8_t>(bootRom, bootRom + bootRomSize);
	}

	return ret;
}

bool Memory::IsRunningBootRom()
{
	// This is not using our functions, because it would cause an infinite loop. So we're going straight to the ram address.
	// 0x0050 is because the real RAM address is 0xFF50, but the IO registers start at 0xFF00, so 0xFF50 - 0xFF00 = 0x0050
	uint8_t val = mIORegisters[0x0050]; 

	return ((val & 1) | (1 >> 8)) == 0;
}

uint8_t Memory::ReadByteAtPointer(KayosBoyPtr ptr)
{
	uint16_t addr = ptr.GetPointerVal();

	if (IsRunningBootRom())
	{
		if (addr < 0x0100)
		{
			return mBootRom[addr];
		}
		else
		{
			return 0xFF;
		}
	}

	if	(addr <= 0x7FFF || (addr >= 0xA000 && addr <= 0xBFFF))
	{
		return mCartridge.read(ptr);
	}
	else if (addr >= 0x8000 && addr <= 0x9FFF) // VRam. Does not check for VBlink interrupts yet.
	{
		return (*mVRam)[addr - 0x8000]; // This will need to be changed when VRam banking is implemented for GBC.
	}
	else if (addr >= 0xC000 && addr <= 0xCFFF)
	{
		return mStaticWRam[addr - 0xC000];
	}
	else if (addr >= 0xD000 && addr <= 0xDFFF)
	{
		return (*mBankWRam)[addr - 0xD000]; // This will need to be changed when WRam banking is implemented for GBC.
	}
	else if(addr >= 0xFE00 && addr <= 0xFE9F)
	{
		return mOAM[addr - 0xFE00];
	}
	else if (addr >= 0xFEA0 && addr <= 0xFEFF)
	{
		return mUnused[addr - 0xFEA0];
	}
	else if (addr >= 0xFF00 && addr <= 0xFF7F)
	{
		return mIORegisters[addr - 0xFF00];
	}
	else if (addr >= 0xFF80 && addr <= 0xFFFE)
	{
		return mHRAM[addr - 0xFF80];
	}
	else if (addr == 0xFFFF)
	{
		return mInterruptRegister;
	}

	return -1; // This will overflow, on purpose.
}

uint16_t Memory::ReadTwoBytesAtPointer(KayosBoyPtr ptr)
{
	uint16_t addr = ptr.GetPointerVal();

	if (IsRunningBootRom())
	{
		if (addr < 0x0100)
		{
			return ReadTwoBytesFromVector(mBootRom, addr);
		}
		else
		{
			return 0xFF;
		}
	}

	if (addr <= 0x7FFF || (addr >= 0xA000 && addr <= 0xBFFF))
	{
		return mCartridge.readTwoBytes(ptr);
	}
	else if (addr >= 0x8000 && addr <= 0x9FFF) // VRam. Does not check for VBlink interrupts yet.
	{
		return ReadTwoBytesFromVector((*mVRam), addr - 0x8000); // This will need to be changed when VRam banking is implemented for GBC.
	}
	else if (addr >= 0xC000 && addr <= 0xCFFF)
	{
		return ReadTwoBytesFromVector(mStaticWRam, addr - 0xC000);
	}
	else if (addr >= 0xD000 && addr <= 0xDFFF)
	{
		return ReadTwoBytesFromVector((*mBankWRam), addr - 0xD000);// This will need to be changed when WRam banking is implemented for GBC.
	}
	else if (addr >= 0xFE00 && addr <= 0xFE9F)
	{
		return ReadTwoBytesFromVector(mOAM, addr - 0xFE00);
	}
	else if (addr >= 0xFEA0 && addr <= 0xFEFF)
	{
		return ReadTwoBytesFromVector(mUnused, addr - 0xFEA0);
	}
	else if (addr >= 0xFF00 && addr <= 0xFF7F)
	{
		return ReadTwoBytesFromVector(mIORegisters, addr - 0xFF00);
	}
	else if (addr >= 0xFF80 && addr <= 0xFFFE)
	{
		return ReadTwoBytesFromVector(mHRAM, addr - 0xFF80);
	}
	else if (addr == 0xFFFF)
	{
		printf("ERROR: Trying to get two bytes from addr 0xFFFF");
		return -1; // This will overflow, on purpose.
	}

	return -1; // This will overflow, on purpose.
}

void Memory::WriteByteAtPointer(KayosBoyPtr ptr, uint8_t val)
{
	uint16_t addr = ptr.GetPointerVal();

	if (addr <= 0x7FFF || (addr >= 0xA000 && addr <= 0xBFFF))
	{
		mCartridge.write(ptr, val);
	}
	else if (addr >= 0x8000 && addr <= 0x9FFF) // VRam. Does not check for VBlink interrupts yet.
	{
		(*mVRam)[addr - 0x8000] = val; // This will need to be changed when VRam banking is implemented for GBC.
	}
	else if (addr >= 0xC000 && addr <= 0xCFFF)
	{
		mStaticWRam[addr - 0xC000] = val;
	}
	else if (addr >= 0xD000 && addr <= 0xDFFF)
	{
		(*mBankWRam)[addr - 0xD000] = val; // This will need to be changed when WRam banking is implemented for GBC.
	}
	else if (addr >= 0xFE00 && addr <= 0xFE9F)
	{
		mOAM[addr - 0xFE00] = val;
	}
	else if (addr >= 0xFEA0 && addr <= 0xFEFF)
	{
		mUnused[addr - 0xFEA0] = val;
	}
	else if (addr >= 0xFF00 && addr <= 0xFF7F)
	{
		mIORegisters[addr - 0xFF00] = val;
	}
	else if (addr >= 0xFF80 && addr <= 0xFFFE)
	{
		mHRAM[addr - 0xFF80] = val;
	}
	else if (addr == 0xFFFF)
	{
		mInterruptRegister = val;
	}
}

void Memory::WriteTwoBytesAtPointer(KayosBoyPtr ptr, uint16_t val)
{
	uint16_t addr = ptr.GetPointerVal();

	if (addr <= 0x7FFF || (addr >= 0xA000 && addr <= 0xBFFF))
	{
		mCartridge.writeTwoBytes(ptr, val);
	}
	else if (addr >= 0x8000 && addr <= 0x9FFF) // VRam. Does not check for VBlink interrupts yet.
	{
		WriteTwoBytesIntoVector((*mVRam), addr - 0x8000, val); // This will need to be changed when VRam banking is implemented for GBC.
	}
	else if (addr >= 0xC000 && addr <= 0xCFFF)
	{
		WriteTwoBytesIntoVector(mStaticWRam, addr - 0xC000, val);
	}
	else if (addr >= 0xD000 && addr <= 0xDFFF)
	{
		WriteTwoBytesIntoVector((*mBankWRam), addr - 0xD000, val);// This will need to be changed when WRam banking is implemented for GBC.
	}
	else if (addr >= 0xFE00 && addr <= 0xFE9F)
	{
		WriteTwoBytesIntoVector(mOAM, addr - 0xFE00, val);
	}
	else if (addr >= 0xFEA0 && addr <= 0xFEFF)
	{
		WriteTwoBytesIntoVector(mUnused, addr - 0xFEA0, val);
	}
	else if (addr >= 0xFF00 && addr <= 0xFF7F)
	{
		WriteTwoBytesIntoVector(mIORegisters, addr - 0xFF00, val);
	}
	else if (addr >= 0xFF80 && addr <= 0xFFFE)
	{
		WriteTwoBytesIntoVector(mHRAM, addr - 0xFF80, val);
	}
	else if (addr == 0xFFFF)
	{
		printf("ERROR: Trying to get two bytes from addr 0xFFFF");
		mInterruptRegister = static_cast<uint8_t>(mInterruptRegister);
	}
}

uint16_t Memory::ReadTwoBytesFromVector(std::vector<uint8_t>& vec, uint16_t addr)
{
	uint8_t byteOne = vec[addr];
	uint8_t byteTwo = vec[addr + 1];

	return static_cast<uint16_t>((byteOne << 8) | byteTwo);
}

void Memory::WriteTwoBytesIntoVector(std::vector<uint8_t>& vec, uint16_t addr, uint16_t val)
{
	uint8_t byteOne = static_cast<uint8_t>(val >> 8);
	uint8_t byteTwo = static_cast<uint8_t>(val);

	vec[addr] = byteOne;
	vec[addr + 1] = byteTwo;
}