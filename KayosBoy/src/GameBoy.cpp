#include "GameBoy.hpp"
#include "KayosBoyUtils.hpp"

GameBoy::GameBoy(CPU& gameboyCPU, Memory& gameboyMemory, Cartridge& cart, Timer& timer) :
	mCycleCount(0),
	mFrameCount(0),
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

 // x - total cycles
 // y - machine cycles
 // z - target framerate
 // a - isVBlank
 // b = x/z = cycles per frame
 // a = 

	// Hack send 60 FPS VBlank
	if (mCycleCount > ((mMachineCycle / 60) * mFrameCount))
	{
		mFrameCount++;
		mMemory.WriteByteAtPointer(KayosBoyPtr(0xFF00 + 0x0044), 1);
	}
	else
	{
		mMemory.WriteByteAtPointer(KayosBoyPtr(0xFF00 + 0x0044), 0);
	}

}