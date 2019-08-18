#include "MBC.hpp"

BaseMBC::BaseMBC(uint8_t* romData, size_t romSize, uint8_t* ramData, size_t ramSize)
{

}

NoMBC::NoMBC(uint8_t* romData, size_t romSize, uint8_t* ramData, size_t ramSize) :
	BaseMBC(romData, romSize, ramData, ramSize)
{

}

void NoMBC::write(KayosBoyPtr& address, uint8_t val)
{

}

uint8_t NoMBC::read(KayosBoyPtr& address)
{
	return 0;
}

MBC1::MBC1(uint8_t* romData, size_t romSize, uint8_t* ramData, size_t ramSize) :
	BaseMBC(romData, romSize, ramData, ramSize)
{

}

void MBC1::write(KayosBoyPtr& address, uint8_t val)
{

}

uint8_t MBC1::read(KayosBoyPtr& address)
{
	return 0;
}

MBC2::MBC2(uint8_t* romData, size_t romSize, uint8_t* ramData, size_t ramSize) :
	BaseMBC(romData, romSize, ramData, ramSize)
{

}

void MBC2::write(KayosBoyPtr& address, uint8_t val)
{

}

uint8_t MBC2::read(KayosBoyPtr& address)
{
	return 0;
}

MBC3::MBC3(uint8_t* romData, size_t romSize, uint8_t* ramData, size_t ramSize) :
	BaseMBC(romData, romSize, ramData, ramSize)
{

}

void MBC3::write(KayosBoyPtr& address, uint8_t val)
{

}

uint8_t MBC3::read(KayosBoyPtr& address)
{
	return 0;
}

MBC5::MBC5(uint8_t* romData, size_t romSize, uint8_t* ramData, size_t ramSize) :
	BaseMBC(romData, romSize, ramData, ramSize)
{

}

void MBC5::write(KayosBoyPtr& address, uint8_t val)
{

}

uint8_t MBC5::read(KayosBoyPtr& address)
{
	return 0;
}