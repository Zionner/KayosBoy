#ifndef _GAMEBOY_H_
#define _GAMEBOY_H_

#include "CPU.hpp"
#include "Cartridge.hpp"
#include "memory.hpp"

class GameBoy
{
	public:
		GameBoy(CPU& gameboyCPU, Memory& gameboyMemory, char* const pathToBootRom, char* const pathToCartridgeRom, char* const pathToCartridgeRam = nullptr);

	protected:
		bool LoadBootROM(char* path);
		bool LoadCartridgeFromFile(char* romPath, char* ramPath);

		const uint32_t mClockCycles = 4194304;
		const uint32_t mMachineCycle = 1048576;

		uint64_t mCycleCount;

		CPU& mCPU;
		Memory& mMemory;
		Cartridge mCartridge;

		// We're loading these from files instead of from a const value
		// Because it allows us to nicely support multiple boot ROMs (and custom boot ROMS).
		// Main reason for doing this: Supporting DMG & GBC Roms. Maybe GBA later on if I want to go that far.
		uint8_t* mBootRom;
		size_t mBootRomSize;
};

#endif // _GAMEBOY_H_