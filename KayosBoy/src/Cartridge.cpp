#include "Cartridge.hpp"
#include "KayosBoyUtils.hpp"

Cartridge::Cartridge() :
	mCartridgeMBC(nullptr)
{

}

Cartridge::Cartridge(uint8_t* romData, size_t romSize, uint8_t* ramData, size_t ramSize)
{
	if (romSize == 0)
	{
		printf("Trying to create a cartridge with a rom of 0. Error!");
		return;
	}

	memcpy_s(&mCartridgeHeader, sizeof(CartridgeHeader), romData + CRA_ExecutionEntryPoint, (CRA_HeaderEnd + 1) - CRA_ExecutionEntryPoint);

	switch (mCartridgeHeader.CartridgeTypeFlag)
	{
		case CT_RomOnly:
			mCartridgeMBC = new NoMBC(romData, romSize, ramData, ramSize);
			break;
		case CT_RomMBC1:
			mCartridgeMBC = new MBC1(romData, romSize, ramData, ramSize);
			break;
		case CT_RomMBC2:
			mCartridgeMBC = new MBC2(romData, romSize, ramData, ramSize);
			break;
		case CT_RomMBC3:
			mCartridgeMBC = new MBC3(romData, romSize, ramData, ramSize);
			break;
		case CT_RomMBC5:
			mCartridgeMBC = new MBC5(romData, romSize, ramData, ramSize);
			break;
		default:
			printf("Unknown/Unsupported Cartridge type");
			break;
	}

}

Cartridge::~Cartridge()
{
	if (mCartridgeMBC != nullptr)
	{
		delete mCartridgeMBC;
		mCartridgeMBC = nullptr;
	}
}

void Cartridge::write(KayosBoyPtr& address, uint8_t val)
{
	mCartridgeMBC->write(address, val);
}

uint8_t Cartridge::read(KayosBoyPtr& address)
{
	return mCartridgeMBC->read(address);
}

