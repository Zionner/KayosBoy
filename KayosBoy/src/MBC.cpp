#include "MBC.hpp"

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
	}
	else
	{
		mStaticRomData = std::vector<uint8_t>(romData, romData + romSize); // Place first 16 KB or rom
	}

	
}

void NoMBC::write(KayosBoyPtr& address, uint8_t val)
{
	printf("NoMBC cartridges have no writable memory. Error! \n");
}

void NoMBC::writeTwoBytes(KayosBoyPtr& address, uint16_t val)
{
	printf("NoMBC cartridges have no writable memory. Error! \n");
}

uint8_t NoMBC::read(KayosBoyPtr& address)
{
	uint16_t addr = address.GetPointerVal();
	return ((addr < 0x4000) ? mStaticRomData[addr] :
							  (*mRomBankData)[addr - 0x4000]);
}

uint16_t NoMBC::readTwoBytes(KayosBoyPtr& address)
{
	uint16_t addr = address.GetPointerVal();
	uint16_t nextAddr = addr + 1;
	uint8_t secondByte = ((addr < 0x4000) ? mStaticRomData[addr] :
										   (*mRomBankData)[addr - 0x4000]);

	uint8_t firstByte = ((nextAddr < 0x4000) ? mStaticRomData[nextAddr] :
												(*mRomBankData)[nextAddr - 0x4000]);

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