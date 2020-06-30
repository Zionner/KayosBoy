#ifndef _GPU_H_
#define _GPU_H_

#include "memory.hpp"

struct SpriteData
{
	uint8_t SpriteY;
	uint8_t SpriteX;
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

enum GBColour : uint8_t
{
	GB_White = 0,
	GB_LightGrey = 1,
	GB_DarkGrey = 2,
	GB_Black = 3
};

struct Colour
{
	Colour()
	{
		Value = 0;
	}

	Colour(GBColour col)
	{
		Value = col;
	}

	uint8_t Value : 2;
};

struct GBPalette 
{
	Colour col0 = Colour(GBColour::GB_White);
	Colour col1 = Colour(GBColour::GB_LightGrey);
	Colour col2 = Colour(GBColour::GB_DarkGrey);
	Colour col3 = Colour(GBColour::GB_Black);
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

union LCDControlRegisterUnion
{
	LCDControlRegister StructuredRegister;
	uint8_t RegisterData;
};

struct LCDStatRegister
{
	uint8_t ScreenMode : 2;
	bool LYCComparisonSignal : 1;
	bool ModeZeroHBlankCheckEnable : 1;
	bool ModeOneVBlankCheckEnable : 1;
	bool ModeTWoOAMCheckEnable : 1;
	bool LYCInteruptEnable : 1;
	bool Unused : 1;
};

union LCDStatRegisterUnion
{
	LCDStatRegister StructuredRegister;
	uint8_t RegisterData;
};

class GPU
{
public:
	GPU(Memory& mem);

	void Tick(uint64_t elapsedTicks);

	const uint64_t ScanlineClockLength = 456;
	const uint8_t ScanLineCount = 144;
	const uint64_t HBlankClockLength = 204;
	const uint64_t OAMClockLength = 80;
	const uint64_t VRAMClockLength = 172;

	bool IsLCDDisplayEnabled();
	bool WindowTileMapDisplaySelect();
	bool IsWindowDisplayEnabled();
	bool BackgroundAndWindowTileDataSelect();
	bool SpriteSize();
	bool SpriteDisplayEnabled();
	bool BackgroundandWindowDisplayPriority();


private:

	LCDControlRegister GetLCDControlRegisterFromMemory();
	LCDStatRegister GetLCDStatRegister();

	void UpdateLCDStatRegister(LCDStatRegister newStatData);

	Memory& mMemory;
	uint64_t mFrameCounter = 0;

	uint64_t mTickCount;
	GBColour FrameBuffer[65536];
};

#endif // _GPU_H_