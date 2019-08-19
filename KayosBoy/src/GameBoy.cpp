#include "GameBoy.hpp"
#include "KayosBoyUtils.hpp"

GameBoy::GameBoy(CPU& gameboyCPU, Memory& gameboyMemory, Cartridge& cart, Timer& timer) :
	mCycleCount(0),
	mCPU(gameboyCPU),
	mMemory(gameboyMemory),
	mKeepRunning(true),
	mCartridge(cart),
	mTimer(timer)
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
	uint64_t elapsedCycles = mCPU.Tick();
	mCycleCount += elapsedCycles;

	mTimer.Tick(elapsedCycles);

}