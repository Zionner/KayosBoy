#include "gpu.hpp"

GPU::GPU(Memory& mem) :
	mMemory(mem)
{

}

void GPU::Tick(uint64_t elapsedTicks)
{
	if (mScanlineTicks >= ScanlineClockLength)
	{
		uint8_t currentScanLine = mMemory.ReadByteAtPointer(KayosBoyPtr(ImportantMemoryAddresses::IMA_CurrentScanline));

		if (currentScanLine >= ScanLineCount)
		{
			mFrameCounter++;
			currentScanLine = 0;

			uint8_t interrupts = mMemory.ReadByteAtPointer(KayosBoyPtr(ImportantMemoryAddresses::IMA_InterruptFlagRegister));
			mMemory.WriteByteAtPointer(KayosBoyPtr(ImportantMemoryAddresses::IMA_InterruptFlagRegister), static_cast<uint8_t>(interrupts | (0 >> 1))); // set bit 0 to 1
		}
		else
		{
			currentScanLine++;
		}

		mMemory.WriteByteAtPointer(KayosBoyPtr(ImportantMemoryAddresses::IMA_CurrentScanline), currentScanLine);
		mScanlineTicks = 0;
	}
	else
	{
		mScanlineTicks += elapsedTicks;
	}
}