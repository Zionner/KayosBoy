#include "memory.hpp"
#include "KayosBoyUtils.hpp"

Memory::Memory(char* const pathToBootRom, Cartridge& cart) :
	mCartridge(cart),
	mDMACycles(DMACycleLength + DMASetupCycles)
{
	mVRam = new std::vector<uint8_t>((ImportantMemoryAddresses::IMA_EndOfVRAM - ImportantMemoryAddresses::IMA_StartOfVRAM) + 1);
	mStaticWRam.resize((ImportantMemoryAddresses::IMA_EndOfStaticWRAM - ImportantMemoryAddresses::IMA_StartOfStaticWRAM) + 1);
	mBankWRam = new std::vector<uint8_t>((ImportantMemoryAddresses::IMA_EndOfSwitchWRAM - ImportantMemoryAddresses::IMA_StartOfSwitchWRAM) + 1);
	mOAM.resize((ImportantMemoryAddresses::IMA_EndOfOAM - ImportantMemoryAddresses::IMA_StartOfOAM) + 1);
	mUnused.resize((ImportantMemoryAddresses::IMA_EndOfUnused - ImportantMemoryAddresses::IMA_StartOfUnused) + 1);
	mIORegisters.resize((ImportantMemoryAddresses::IMA_EndOfIORegisters- ImportantMemoryAddresses::IMA_StartOfIORegisters) + 1);
	mHRAM.resize((ImportantMemoryAddresses::IMA_EndOfHRAM - ImportantMemoryAddresses::IMA_StartOfHRAM) + 1); // Last byte is for the interrupt register
	mInterruptRegister.resize(0x0001); // This is just a one byte flag register. It's only a vector for ease of use with the rest of the memory.

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

void Memory::HandleDMA(uint64_t elapsedTicks)
{
	uint8_t dmaRegister = ReadByteAtPointer(KayosBoyPtr(ImportantMemoryAddresses::IMA_DMAAddress));

	if (dmaRegister == mPreviousDMARegisterValue)
	{
		if (mDMACycles < DMASetupCycles)
		{
			mDMACycles += elapsedTicks;
			return;
		}
		else if (mDMACycles >= (DMACycleLength + DMASetupCycles))
		{
			return;
		}
	}
	else
	{
		mDMACycles = elapsedTicks;
		dmaRegister = mPreviousDMARegisterValue;
		return;
	}

	mPreviousDMARegisterValue = dmaRegister;

	uint8_t remainingTicksFromLastUpdate = mDMACycles % 4;

	if (remainingTicksFromLastUpdate > 0)
	{
		mDMACycles -= remainingTicksFromLastUpdate;
		elapsedTicks += remainingTicksFromLastUpdate;
	}

	while(elapsedTicks >= 4 && mDMACycles < (DMACycleLength + DMASetupCycles))
	{
		uint8_t lowerPtrByte = floor(mDMACycles / 4);
		uint16_t srcptr = (dmaRegister << 8) + lowerPtrByte; // This is not mapped correctly.
		uint16_t destptr = ImportantMemoryAddresses::IMA_StartOfOAM + (8 >> lowerPtrByte);
		WriteByteAtPointer(destptr, ReadByteAtPointer(srcptr));

		mDMACycles += 4;
		elapsedTicks -= 4;
	}

	mDMACycles += elapsedTicks;
}

bool Memory::IsDMAInProgress()
{
	return mDMACycles >= DMASetupCycles && mDMACycles <= (DMASetupCycles + DMACycleLength);
}

bool Memory::IsRunningBootRom()
{
	// 0x0050 is because the real RAM address is 0xFF50, but the IO registers start at 0xFF00, so 0xFF50 - 0xFF00 = 0x0050
	uint8_t val = mIORegisters[ImportantMemoryAddresses::IMA_BootROMEnabledFlag - ImportantMemoryAddresses::IMA_StartOfIORegisters];

	return ((val & 1) | (1 >> 8)) == 0;
}

uint8_t Memory::ReadByteAtPointer(KayosBoyPtr ptr)
{
	uint16_t addr = ptr.GetPointerVal();

	if (IsRunningBootRom())
	{
		if (addr <= ImportantMemoryAddresses::IMA_BootRomEnd)
		{
			return mBootRom[addr];
		}
	}

	if	(addr <= IMA_EndOfSwitableROM || (addr >= ImportantMemoryAddresses::IMA_StartOfCartridgeRam && addr <= ImportantMemoryAddresses::IMA_EndOfCartridgeRam))
	{
		return mCartridge.read(ptr);
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfVRAM && addr <= ImportantMemoryAddresses::IMA_EndOfVRAM) // VRam. Does not check for VBlink interrupts yet.
	{
		return (*mVRam)[addr - ImportantMemoryAddresses::IMA_StartOfVRAM]; // This will need to be changed when VRam banking is implemented for GBC.
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfStaticWRAM && addr <= ImportantMemoryAddresses::IMA_EndOfStaticWRAM)
	{
		return mStaticWRam[addr - ImportantMemoryAddresses::IMA_StartOfStaticWRAM];
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfSwitchWRAM && addr <= ImportantMemoryAddresses::IMA_EndOfSwitchWRAM)
	{
		return (*mBankWRam)[addr - ImportantMemoryAddresses::IMA_StartOfSwitchWRAM]; // This will need to be changed when WRam banking is implemented for GBC.
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfStaticWRAMEcho && addr <= ImportantMemoryAddresses::IMA_EndOfStaticWRAMEcho)
	{
		return mStaticWRam[addr - ImportantMemoryAddresses::IMA_StartOfStaticWRAMEcho];
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfSwitchWRAMEcho && addr <= ImportantMemoryAddresses::IMA_EndOfSwitchWRAMEcho)
	{
		return (*mBankWRam)[addr - ImportantMemoryAddresses::IMA_StartOfSwitchWRAMEcho]; // This will need to be changed when WRam banking is implemented for GBC.
	}
	else if(addr >= ImportantMemoryAddresses::IMA_StartOfOAM && addr <= ImportantMemoryAddresses::IMA_EndOfOAM)
	{
		return mOAM[addr - ImportantMemoryAddresses::IMA_StartOfOAM];
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfUnused && addr <= ImportantMemoryAddresses::IMA_EndOfUnused)
	{
		return mUnused[addr - ImportantMemoryAddresses::IMA_StartOfUnused];
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfIORegisters && addr <= ImportantMemoryAddresses::IMA_EndOfIORegisters)
	{
		return mIORegisters[addr - ImportantMemoryAddresses::IMA_StartOfIORegisters];
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfHRAM && addr <= ImportantMemoryAddresses::IMA_EndOfHRAM)
	{
		return mHRAM[addr - ImportantMemoryAddresses::IMA_StartOfHRAM];
	}
	else if (addr == ImportantMemoryAddresses::IMA_InterruptEnableFlags)
	{
		return mInterruptRegister[addr - ImportantMemoryAddresses::IMA_InterruptEnableFlags];
	}

	return -1; // This will overflow, on purpose.
}

uint16_t Memory::ReadTwoBytesAtPointer(KayosBoyPtr ptr)
{
	uint16_t addr = ptr.GetPointerVal();

	if (IsRunningBootRom())
	{
		if (addr < ImportantMemoryAddresses::IMA_BootRomEnd)
		{
			return ReadTwoBytesFromVector(mBootRom, addr);
		}
	}

	if (addr <= ImportantMemoryAddresses::IMA_EndOfSwitableROM || (addr >= ImportantMemoryAddresses::IMA_StartOfCartridgeRam && addr <= ImportantMemoryAddresses::IMA_EndOfCartridgeRam))
	{
		return mCartridge.readTwoBytes(ptr);
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfVRAM && addr <= ImportantMemoryAddresses::IMA_EndOfVRAM) // VRam. Does not check for VBlink interrupts yet.
	{
		if(addr == ImportantMemoryAddresses::IMA_EndOfVRAM)
		{
			return ReadTwoBytesFromTwoVectors((*mVRam), mStaticWRam, addr - ImportantMemoryAddresses::IMA_StartOfVRAM);
		}

		return ReadTwoBytesFromVector((*mVRam), addr - ImportantMemoryAddresses::IMA_StartOfVRAM); // This will need to be changed when VRam banking is implemented for GBC.
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfStaticWRAM && addr <= ImportantMemoryAddresses::IMA_EndOfStaticWRAM)
	{
		if (addr == ImportantMemoryAddresses::IMA_EndOfStaticWRAM)
		{
			return ReadTwoBytesFromTwoVectors(mStaticWRam, (*mBankWRam), addr - ImportantMemoryAddresses::IMA_StartOfStaticWRAM);
		}

		return ReadTwoBytesFromVector(mStaticWRam, addr - ImportantMemoryAddresses::IMA_StartOfStaticWRAM);
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfSwitchWRAM && addr <= ImportantMemoryAddresses::IMA_EndOfSwitchWRAM)
	{
		if (addr == ImportantMemoryAddresses::IMA_EndOfSwitchWRAM)
		{
			return ReadTwoBytesFromTwoVectors((*mBankWRam), mStaticWRam, addr - ImportantMemoryAddresses::IMA_StartOfSwitchWRAM);
		}

		return ReadTwoBytesFromVector((*mBankWRam), addr - ImportantMemoryAddresses::IMA_StartOfSwitchWRAM);// This will need to be changed when WRam banking is implemented for GBC.
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfStaticWRAMEcho && addr <= ImportantMemoryAddresses::IMA_EndOfStaticWRAMEcho)
	{
		if (addr == ImportantMemoryAddresses::IMA_EndOfStaticWRAMEcho)
		{
			return ReadTwoBytesFromTwoVectors(mStaticWRam, (*mBankWRam), addr - ImportantMemoryAddresses::IMA_StartOfStaticWRAMEcho);
		}

		return ReadTwoBytesFromVector(mStaticWRam, addr - ImportantMemoryAddresses::IMA_StartOfStaticWRAMEcho);
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfSwitchWRAMEcho && addr <= ImportantMemoryAddresses::IMA_EndOfSwitchWRAMEcho)
	{
		if (addr == ImportantMemoryAddresses::IMA_EndOfSwitchWRAMEcho)
		{
			return ReadTwoBytesFromTwoVectors((*mBankWRam), mOAM, addr - ImportantMemoryAddresses::IMA_StartOfSwitchWRAMEcho);
		}

		return ReadTwoBytesFromVector((*mBankWRam), addr - ImportantMemoryAddresses::IMA_StartOfSwitchWRAMEcho);// This will need to be changed when WRam banking is implemented for GBC.
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfOAM && addr <= ImportantMemoryAddresses::IMA_EndOfOAM)
	{
		if (addr == ImportantMemoryAddresses::IMA_EndOfOAM)
		{
			return ReadTwoBytesFromTwoVectors(mOAM, mUnused, addr - ImportantMemoryAddresses::IMA_StartOfOAM);
		}

		return ReadTwoBytesFromVector(mOAM, addr - ImportantMemoryAddresses::IMA_StartOfOAM);
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfUnused && addr <= ImportantMemoryAddresses::IMA_EndOfUnused)
	{
		if (addr == ImportantMemoryAddresses::IMA_EndOfUnused)
		{
			return ReadTwoBytesFromTwoVectors(mUnused, mIORegisters, addr - ImportantMemoryAddresses::IMA_StartOfUnused);
		}

		return ReadTwoBytesFromVector(mUnused, addr - ImportantMemoryAddresses::IMA_StartOfUnused);
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfIORegisters && addr <= ImportantMemoryAddresses::IMA_EndOfIORegisters)
	{
		if (addr == ImportantMemoryAddresses::IMA_EndOfIORegisters)
		{
			return ReadTwoBytesFromTwoVectors(mIORegisters, mHRAM, addr - ImportantMemoryAddresses::IMA_StartOfIORegisters);
		}

		return ReadTwoBytesFromVector(mIORegisters, addr - ImportantMemoryAddresses::IMA_StartOfIORegisters);
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfHRAM && addr <= ImportantMemoryAddresses::IMA_EndOfHRAM)
	{
		if (addr == ImportantMemoryAddresses::IMA_EndOfHRAM)
		{
			return ReadTwoBytesFromTwoVectors(mHRAM, mInterruptRegister, addr - ImportantMemoryAddresses::IMA_StartOfHRAM);
		}

		return ReadTwoBytesFromVector(mHRAM, addr - ImportantMemoryAddresses::IMA_StartOfHRAM);
	}
	else if (addr == ImportantMemoryAddresses::IMA_InterruptEnableFlags)
	{
		printf("ERROR: Trying to get two bytes from addr 0xFFFF \n");
		return -1; // This will overflow, on purpose.
	}

	return -1; // This will overflow, on purpose.
}

void Memory::WriteByteAtPointer(KayosBoyPtr ptr, uint8_t val)
{
	uint16_t addr = ptr.GetPointerVal();

	if (addr <= ImportantMemoryAddresses::IMA_EndOfSwitableROM || (addr >= ImportantMemoryAddresses::IMA_StartOfCartridgeRam && addr <= ImportantMemoryAddresses::IMA_EndOfCartridgeRam))
	{
		mCartridge.write(ptr, val);
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfVRAM && addr <= ImportantMemoryAddresses::IMA_EndOfVRAM) // VRam. Does not check for VBlink interrupts yet.
	{
		(*mVRam)[addr - ImportantMemoryAddresses::IMA_StartOfVRAM] = val; // This will need to be changed when VRam banking is implemented for GBC.
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfStaticWRAM && addr <= ImportantMemoryAddresses::IMA_EndOfStaticWRAM)
	{
		mStaticWRam[addr - ImportantMemoryAddresses::IMA_StartOfStaticWRAM] = val;
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfSwitchWRAM && addr <= ImportantMemoryAddresses::IMA_EndOfSwitchWRAM)
	{
		(*mBankWRam)[addr - ImportantMemoryAddresses::IMA_StartOfSwitchWRAM] = val; // This will need to be changed when WRam banking is implemented for GBC.
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfStaticWRAMEcho && addr <= ImportantMemoryAddresses::IMA_EndOfStaticWRAMEcho)
	{
		mStaticWRam[addr - ImportantMemoryAddresses::IMA_StartOfStaticWRAMEcho] = val;
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfSwitchWRAMEcho && addr <= ImportantMemoryAddresses::IMA_EndOfSwitchWRAMEcho)
	{
		(*mBankWRam)[addr - ImportantMemoryAddresses::IMA_StartOfSwitchWRAMEcho] = val; // This will need to be changed when WRam banking is implemented for GBC.
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfOAM && addr <= ImportantMemoryAddresses::IMA_EndOfOAM)
	{
		mOAM[addr - ImportantMemoryAddresses::IMA_StartOfOAM] = val;
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfUnused && addr <= ImportantMemoryAddresses::IMA_EndOfUnused)
	{
		mUnused[addr - ImportantMemoryAddresses::IMA_StartOfUnused] = val;
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfIORegisters && addr <= ImportantMemoryAddresses::IMA_EndOfIORegisters)
	{
		mIORegisters[addr - ImportantMemoryAddresses::IMA_StartOfIORegisters] = val;
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfHRAM && addr <= ImportantMemoryAddresses::IMA_EndOfHRAM)
	{
		mHRAM[addr - ImportantMemoryAddresses::IMA_StartOfHRAM] = val;
	}
	else if (addr == ImportantMemoryAddresses::IMA_InterruptEnableFlags)
	{
		mInterruptRegister[0x00] = val;
	}
}

void Memory::WriteTwoBytesAtPointer(KayosBoyPtr ptr, uint16_t val)
{
	uint16_t addr = ptr.GetPointerVal();

	if (addr <= ImportantMemoryAddresses::IMA_EndOfSwitableROM || (addr >= ImportantMemoryAddresses::IMA_StartOfCartridgeRam && addr <= ImportantMemoryAddresses::IMA_EndOfCartridgeRam))
	{
		mCartridge.writeTwoBytes(ptr, val);
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfVRAM && addr <= ImportantMemoryAddresses::IMA_EndOfVRAM) // VRam. Does not check for VBlink interrupts yet.
	{
		if (addr == ImportantMemoryAddresses::IMA_EndOfVRAM)
		{
			return WriteTwoBytesIntoTwoVectors((*mVRam), mStaticWRam, addr - ImportantMemoryAddresses::IMA_StartOfVRAM, val);
		}

		WriteTwoBytesIntoVector((*mVRam), addr - ImportantMemoryAddresses::IMA_StartOfVRAM, val); // This will need to be changed when VRam banking is implemented for GBC.
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfStaticWRAM && addr <= ImportantMemoryAddresses::IMA_EndOfStaticWRAM)
	{
		if (addr == ImportantMemoryAddresses::IMA_EndOfStaticWRAM)
		{
			return WriteTwoBytesIntoTwoVectors(mStaticWRam, (*mBankWRam), addr - ImportantMemoryAddresses::IMA_StartOfStaticWRAM, val);
		}

		WriteTwoBytesIntoVector(mStaticWRam, addr - ImportantMemoryAddresses::IMA_StartOfStaticWRAM, val);
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfSwitchWRAM && addr <= ImportantMemoryAddresses::IMA_EndOfSwitchWRAM)
	{
		if (addr == ImportantMemoryAddresses::IMA_EndOfSwitchWRAM)
		{
			return WriteTwoBytesIntoTwoVectors((*mBankWRam), mStaticWRam, addr - ImportantMemoryAddresses::IMA_StartOfSwitchWRAM, val);
		}

		WriteTwoBytesIntoVector((*mBankWRam), addr - ImportantMemoryAddresses::IMA_StartOfSwitchWRAM, val);// This will need to be changed when WRam banking is implemented for GBC.
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfStaticWRAMEcho && addr <= ImportantMemoryAddresses::IMA_EndOfStaticWRAMEcho)
	{
		if (addr == ImportantMemoryAddresses::IMA_EndOfStaticWRAMEcho)
		{
			return WriteTwoBytesIntoTwoVectors(mStaticWRam, (*mBankWRam), addr - ImportantMemoryAddresses::IMA_StartOfStaticWRAMEcho, val);
		}

		WriteTwoBytesIntoVector(mStaticWRam, addr - ImportantMemoryAddresses::IMA_StartOfStaticWRAMEcho, val);
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfSwitchWRAMEcho && addr <= ImportantMemoryAddresses::IMA_EndOfSwitchWRAMEcho)
	{
		if (addr == ImportantMemoryAddresses::IMA_EndOfSwitchWRAMEcho)
		{
			return WriteTwoBytesIntoTwoVectors((*mBankWRam), mOAM, addr - ImportantMemoryAddresses::IMA_StartOfSwitchWRAMEcho, val);
		}

		WriteTwoBytesIntoVector((*mBankWRam), addr - ImportantMemoryAddresses::IMA_StartOfSwitchWRAMEcho, val);// This will need to be changed when WRam banking is implemented for GBC.
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfOAM && addr <= ImportantMemoryAddresses::IMA_EndOfOAM)
	{
		if (addr == ImportantMemoryAddresses::IMA_EndOfOAM)
		{
			return WriteTwoBytesIntoTwoVectors(mOAM, mUnused, addr - ImportantMemoryAddresses::IMA_StartOfOAM, val);
		}

		WriteTwoBytesIntoVector(mOAM, addr - ImportantMemoryAddresses::IMA_StartOfOAM, val);
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfUnused && addr <= ImportantMemoryAddresses::IMA_EndOfUnused)
	{
		if (addr == ImportantMemoryAddresses::IMA_EndOfUnused)
		{
			return WriteTwoBytesIntoTwoVectors(mUnused, mIORegisters, addr - ImportantMemoryAddresses::IMA_StartOfUnused, val);
		}

		WriteTwoBytesIntoVector(mUnused, addr - ImportantMemoryAddresses::IMA_StartOfUnused, val);
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfIORegisters && addr <= ImportantMemoryAddresses::IMA_EndOfIORegisters)
	{
		if (addr == ImportantMemoryAddresses::IMA_EndOfIORegisters)
		{
			return WriteTwoBytesIntoTwoVectors(mIORegisters, mHRAM, addr - ImportantMemoryAddresses::IMA_StartOfIORegisters, val);
		}

		WriteTwoBytesIntoVector(mIORegisters, addr - ImportantMemoryAddresses::IMA_StartOfIORegisters, val);
	}
	else if (addr >= ImportantMemoryAddresses::IMA_StartOfHRAM && addr <= ImportantMemoryAddresses::IMA_EndOfHRAM)
	{
		if (addr == ImportantMemoryAddresses::IMA_EndOfHRAM)
		{
			return WriteTwoBytesIntoTwoVectors(mHRAM, mInterruptRegister, addr - ImportantMemoryAddresses::IMA_StartOfHRAM, val);
		}

		WriteTwoBytesIntoVector(mHRAM, addr - ImportantMemoryAddresses::IMA_StartOfHRAM, val);
	}
	else if (addr == ImportantMemoryAddresses::IMA_InterruptEnableFlags)
	{
		printf("ERROR: Trying to get two bytes from addr 0xFFFF \n");
	}
}

uint16_t Memory::ReadTwoBytesFromVector(std::vector<uint8_t>& vec, uint16_t addr)
{
	uint8_t byteTwo = vec[addr];
	uint8_t byteOne = vec[addr + 1];

	return static_cast<uint16_t>((byteOne << 8) | byteTwo);
}

uint16_t Memory::ReadTwoBytesFromTwoVectors(std::vector<uint8_t>& vec1, std::vector<uint8_t>& vec2, uint16_t addr)
{
	uint8_t byteTwo = vec1[addr];
	uint8_t byteOne = vec2[0x00];

	return static_cast<uint16_t>((byteOne << 8) | byteTwo);
}

void Memory::WriteTwoBytesIntoVector(std::vector<uint8_t>& vec, uint16_t addr, uint16_t val)
{
	uint8_t byteTwo = static_cast<uint8_t>(val >> 8);
	uint8_t byteOne = static_cast<uint8_t>(val);

	vec[addr] = byteOne;
	vec[addr + 1] = byteTwo;
}

void Memory::WriteTwoBytesIntoTwoVectors(std::vector<uint8_t>& vec1, std::vector<uint8_t>& vec2, uint16_t addr, uint16_t val)
{
	uint8_t byteTwo = static_cast<uint8_t>(val >> 8);
	uint8_t byteOne = static_cast<uint8_t>(val);

	vec1[addr] = byteOne;
	vec2[0x00] = byteTwo;
}