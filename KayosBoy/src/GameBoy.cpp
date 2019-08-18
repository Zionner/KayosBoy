#include "GameBoy.hpp"
#include "KayosBoyUtils.hpp"

GameBoy::GameBoy(CPU& gameboyCPU, Memory& gameboyMemory, char* const pathToBootRom, char* const pathToCartridgeRom, char* const pathToCartridgeRam) :
	mCycleCount(0),
	mCPU(gameboyCPU),
	mMemory(gameboyMemory),
	mKeepRunning(true)
{
	LoadBootROM(pathToBootRom);
	LoadCartridgeFromFile(pathToCartridgeRom, pathToCartridgeRam);
}

bool GameBoy::LoadBootROM(char* const path)
{
	mBootRomSize = LoadBinaryFile(path, &mBootRom);
	return mBootRomSize != 0;
}

bool GameBoy::LoadCartridgeFromFile(char* const romPath, char* ramPath)
{
	uint8_t* rawCartridgeRom = nullptr;
	uint8_t* rawCartridgeRam = nullptr;

	size_t romRet = LoadBinaryFile(romPath, &rawCartridgeRom);

	if (romRet == 0)
	{
		delete[] rawCartridgeRom;
		return false;
	}

	size_t ramRet = LoadBinaryFile(ramPath, &rawCartridgeRam);

	if (ramRet == 0)
	{
		printf("No cartridge RAM found.");
	}

	mCartridge = Cartridge(rawCartridgeRom, romRet, rawCartridgeRam, ramRet);

	delete[] rawCartridgeRom;
	delete[] rawCartridgeRam;

	return true;
}

void GameBoy::Tick()
{
	while(mKeepRunning)
	mCycleCount += mCPU.Tick();
}