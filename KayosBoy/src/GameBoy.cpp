#include "GameBoy.hpp"
#include "KayosBoyUtils.hpp"

GameBoy::GameBoy(CPU& gameboyCPU, Memory& gameboyMemory, Cartridge& cart, Timer& timer, GPU& gpu) :
	mCycleCount(0),
	mFrameCount(0),
	mCPU(gameboyCPU),
	mMemory(gameboyMemory),
	mKeepRunning(true),
	mCartridge(cart),
	mTimer(timer),
	mGPU(gpu)
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
	mGPU.Tick(elapsedCycles);

}