#include "GameBoy.hpp"
#include "KayosBoyUtils.hpp"

GameBoy::GameBoy(char* const pathToBootRom, CPU& gameboyCPU, Memory& gameboyMemory, Cartridge& cart) :
	mCycleCount(0),
	mCPU(gameboyCPU),
	mMemory(gameboyMemory),
	mKeepRunning(true),
	mCartridge(cart)
{
	LoadBootROM(pathToBootRom);
}

bool GameBoy::LoadBootROM(char* const path)
{
	mBootRomSize = LoadBinaryFile(path, &mBootRom);
	return mBootRomSize != 0;
}

void GameBoy::Run()
{
	while (mKeepRunning)
	{
		Tick();
	}
}

void GameBoy::Tick()
{
	mCycleCount += mCPU.Tick();
}