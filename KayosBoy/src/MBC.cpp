#include "MBC.hpp"
#include "memory.hpp"

BaseMBC::BaseMBC(uint8_t* romData, size_t romSize, uint8_t* ramData, size_t ramSize)
{

}

NoMBC::NoMBC(uint8_t* romData, size_t romSize, uint8_t* ramData, size_t ramSize) :
	BaseMBC(romData, romSize, ramData, ramSize)
{
	uint16_t bankSize = 0x4000;

	if (romSize > bankSize)
	{
		size_t remainingData = romSize - bankSize;
		mStaticRomData = std::vector<uint8_t>(romData, romData + bankSize);
		mRomBankData = new std::vector<uint8_t>(romData + bankSize, romData + bankSize + remainingData); // Place the rest into the second bank.

		if (ramSize > 0)
		{
			mRamBankData = new std::vector<uint8_t>(ramData, ramData + ramSize);
		}
		else
		{
			mRamBankData = new std::vector<uint8_t>((ImportantMemoryAddresses::IMA_EndOfCartridgeRam - ImportantMemoryAddresses::IMA_StartOfCartridgeRam) + 1);
		}
	}
	else
	{
		mStaticRomData = std::vector<uint8_t>(romData, romData + romSize); // Place first 16 KB or rom
	}

	
}

void NoMBC::write(KayosBoyPtr& address, uint8_t val)
{
	if (address.GetPointerVal() >= ImportantMemoryAddresses::IMA_StartOfCartridgeRam && address.GetPointerVal() <= ImportantMemoryAddresses::IMA_EndOfCartridgeRam)
	{
		(*mRamBankData)[address.GetPointerVal() - ImportantMemoryAddresses::IMA_StartOfCartridgeRam] = val;
		return;
	}

	// This is often reached when trying to change ROM banks, but we don't have ROM banks for NOMBC.
	//printf("MBC Memory Write Error! Address: 0x%04x \n", address.GetPointerVal());
}

void NoMBC::writeTwoBytes(KayosBoyPtr& address, uint16_t val)
{
	if (address.GetPointerVal() >= ImportantMemoryAddresses::IMA_StartOfCartridgeRam && address.GetPointerVal() <= (ImportantMemoryAddresses::IMA_EndOfCartridgeRam - 1))
	{
		uint8_t byteTwo = static_cast<uint8_t>(val >> 8);
		uint8_t byteOne = static_cast<uint8_t>(val);

		(*mRamBankData)[address.GetPointerVal() - ImportantMemoryAddresses::IMA_StartOfCartridgeRam] = byteOne;
		(*mRamBankData)[(address.GetPointerVal() + 1) - ImportantMemoryAddresses::IMA_StartOfCartridgeRam] = byteTwo;
		return;
	}

	if (address.GetPointerVal() == ImportantMemoryAddresses::IMA_EndOfCartridgeRam)
	{
		printf("Trying to write two bytes to end of MBC Ram (0xBFFF). Error! \n");
		return;
	}

	printf("MBC Memory Write Error! Address: 0x%04x \n", address.GetPointerVal());
}

uint8_t NoMBC::read(KayosBoyPtr& address)
{
	uint16_t addr = address.GetPointerVal();

	if (addr >= ImportantMemoryAddresses::IMA_StartOfCartridgeRam && addr <= ImportantMemoryAddresses::IMA_EndOfCartridgeRam)
	{
		return (*mRamBankData)[addr - ImportantMemoryAddresses::IMA_StartOfCartridgeRam];
	}

	return ((addr < 0x4000) ? mStaticRomData[addr] :
							  (*mRomBankData)[addr - 0x4000]);
}

uint16_t NoMBC::readTwoBytes(KayosBoyPtr& address)
{
	uint16_t addr = address.GetPointerVal();
	uint16_t nextAddr = addr + 1;
	uint8_t secondByte = 0;
	uint8_t firstByte = 0;

	if (address.GetPointerVal() >= ImportantMemoryAddresses::IMA_StartOfCartridgeRam && address.GetPointerVal() <= (ImportantMemoryAddresses::IMA_EndOfCartridgeRam - 1))
	{
		firstByte = (*mRamBankData)[addr - ImportantMemoryAddresses::IMA_StartOfCartridgeRam];
		secondByte = (*mRamBankData)[nextAddr - ImportantMemoryAddresses::IMA_StartOfCartridgeRam];
	}
	else if (address.GetPointerVal() == ImportantMemoryAddresses::IMA_EndOfCartridgeRam)
	{
		printf("Trying to read two bytes to end of MBC Ram (0xBFFF). Error! \n");
		return 0xFFFF;
	}
	else
	{
		secondByte = ((addr < 0x4000) ? mStaticRomData[addr] :
			(*mRomBankData)[addr - 0x4000]);

		firstByte = ((nextAddr < 0x4000) ? mStaticRomData[nextAddr] :
			(*mRomBankData)[nextAddr - 0x4000]);
	}
	

	return static_cast<uint16_t>((firstByte << 8) | secondByte);
}

MBC1::MBC1(uint8_t* romData, size_t romSize, uint8_t* ramData, size_t ramSize) :
	BaseMBC(romData, romSize, ramData, ramSize)
{

}

void MBC1::write(KayosBoyPtr& address, uint8_t val)
{
	printf("MBC1 writes unimplemented \n");
}

void MBC1::writeTwoBytes(KayosBoyPtr& address, uint16_t val)
{
	printf("MBC1 writes unimplemented \n");
}

uint8_t MBC1::read(KayosBoyPtr& address)
{
	return 0;
}

uint16_t MBC1::readTwoBytes(KayosBoyPtr& address)
{
	return 0;
}

MBC2::MBC2(uint8_t* romData, size_t romSize, uint8_t* ramData, size_t ramSize) :
	BaseMBC(romData, romSize, ramData, ramSize)
{

}

void MBC2::write(KayosBoyPtr& address, uint8_t val)
{
	printf("MBC2 writes unimplemented \n");
}

void MBC2::writeTwoBytes(KayosBoyPtr& address, uint16_t val)
{
	printf("MBC2 writes unimplemented \n");
}

uint8_t MBC2::read(KayosBoyPtr& address)
{
	return 0;
}

uint16_t MBC2::readTwoBytes(KayosBoyPtr& address)
{
	return 0;
}

MBC3::MBC3(uint8_t* romData, size_t romSize, uint8_t* ramData, size_t ramSize) :
	BaseMBC(romData, romSize, ramData, ramSize)
{

}

void MBC3::write(KayosBoyPtr& address, uint8_t val)
{
	printf("MBC3 writes unimplemented \n");
}

void MBC3::writeTwoBytes(KayosBoyPtr& address, uint16_t val)
{
	printf("MBC3 writes unimplemented \n");
}

uint8_t MBC3::read(KayosBoyPtr& address)
{
	return 0;
}

uint16_t MBC3::readTwoBytes(KayosBoyPtr& address)
{
	return 0;
}

MBC5::MBC5(uint8_t* romData, size_t romSize, uint8_t* ramData, size_t ramSize) :
	BaseMBC(romData, romSize, ramData, ramSize)
{

}

void MBC5::write(KayosBoyPtr& address, uint8_t val)
{
	printf("MBC5 writes unimplemented \n");
}

void MBC5::writeTwoBytes(KayosBoyPtr& address, uint16_t val)
{
	printf("MBC5 writes unimplemented \n");
}

uint8_t MBC5::read(KayosBoyPtr& address)
{
	return 0;
}

uint16_t MBC5::readTwoBytes(KayosBoyPtr& address)
{
	return 0;
}