#include "GameBoy.hpp"
#include "KayosBoyUtils.hpp"

GameBoy::GameBoy(CPU& gameboyCPU, Memory& gameboyMemory, Cartridge& cart) :
	mCycleCount(0),
	mCPU(gameboyCPU),
	mMemory(gameboyMemory),
	mKeepRunning(true),
	mCartridge(cart)
{
	
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