#ifndef _GAMEBOY_H_
#define _GAMEBOY_H_

#include "CPU.hpp"
#include "Cartridge.hpp"
#include "memory.hpp"
#include "CPU.hpp"

class GameBoy
{
	public:
		GameBoy(Cartridge& cartToLoad);

	protected:
		const uint32_t mClockCycles = 4194304;
		const uint32_t mMachineCycle = 1048576;

		uint64_t mCycleCount;

		CPU mCPU;
		Memory mMemory;
		Cartridge& mCartridge;



};

#endif // _GAMEBOY_H_