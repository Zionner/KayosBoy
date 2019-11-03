#ifndef _GPU_H_
#define _GPU_H_

#include "memory.hpp"

struct SpriteData
{
	uint8_t SpriteYLoc;
	uint8_t SpriteXLoc;
	uint8_t TileNum;
	uint8_t PaletteBitOne : 1;
	uint8_t PaletteBitTwo : 1;
	uint8_t PaletteBitThree : 1;
	uint8_t VRamBank : 1;
	uint8_t PaletteNumber : 1;
	uint8_t XFlip : 1;
	uint8_t YFlip : 1;
	uint8_t RenderPriority : 1;
};

enum VideoMode : uint8_t
{
	VM_HBlank = 0,
	VM_VBlank = 1,
	VM_OAM = 2,
	VM_Transfer = 3
};

struct GBPalette 
{
	Colour col0 = GBColour::GB_White;
	Colour col1 = GBColour::GB_LightGrey;
	Colour col2 = GBColour::GB_DarkGrey;
	Colour col3 = GBColour::GB_Black;
};

struct Colour
{
	uint8_t Value : 2;

	uint8_t& operator=(const uint8_t& other)
	{
		Value = other;
	}
};

enum GBColour : uint8_t
{
	GB_White = 0,
	GB_LightGrey = 1,
	GB_DarkGrey = 2,
	GB_Black = 3
};

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