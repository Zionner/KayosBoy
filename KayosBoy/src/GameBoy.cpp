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

	// Hack send 60 FPS VBlank
	if (mCycleCount > ((mMachineCycle / 60) * mFrameCount))
	{
		mFrameCount++;

		uint8_t interrupts = mMemory.ReadByteAtPointer(KayosBoyPtr(ImportantMemoryAddresses::IMA_InterruptFlagRegister));
		mMemory.WriteByteAtPointer(KayosBoyPtr(ImportantMemoryAddresses::IMA_InterruptFlagRegister), static_cast<uint8_t>(interrupts | (0 >> 1))); // set bit 0 to 1
	}

}