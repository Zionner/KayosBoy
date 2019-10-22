#ifndef _GPU_H_
#define _GPU_H_

#include "memory.hpp"

struct LCDControlRegister
{
	bool BackgroundEnabled : 1; // This is different for different between GBC and DMG. Revisit this when looking into GBC.
	bool SpritesEnabled : 1;
	bool SpriteSize : 1;
	bool BackgroundTileMap : 1;
	bool BackgroundWindowTileSet : 1;
	bool WindowEnabled : 1;
	bool WindowTileMpa : 1;
	bool LCDPowerEnabled : 1;
};

struct LCDStatRegister
{
	uint8_t ScreenMode : 2;
	bool LYCComparisonSignal : 1;
	bool ModeZeroHBlankCheckEnable : 1;
	bool ModeOneVBlankCheckEnable : 1;
	bool ModeTWoOAMCheckEnable : 1;
	bool LYCCheckEnable : 1;
	const bool Unused : 1;
};

class GPU
{
public:
	GPU(Memory& mem);

	void Tick(uint64_t elapsedTicks);

	const uint64_t ScanlineClockLength = 456;
	const uint8_t ScanLineCount = 154;

private:
	Memory& mMemory;
	uint64_t mFrameCounter = 0;

	uint64_t mScanlineTicks;
};

#endif // _GPU_H_