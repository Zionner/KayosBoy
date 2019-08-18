#include "Cartridge.hpp"
#include "KayosBoyUtils.hpp"

Cartridge::Cartridge()
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
}

