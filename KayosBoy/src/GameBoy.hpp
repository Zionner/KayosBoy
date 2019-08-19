#ifndef _GAMEBOY_H_
#define _GAMEBOY_H_

#include "CPU.hpp"
#include "Cartridge.hpp"
#include "timer.hpp"

class GameBoy
{
	public:
		GameBoy(CPU& gameboyCPU, Memory& gameboyMemory, Cartridge& cart, Timer& timer);

		void Run();

	protected:
		void Tick();

		bool mKeepRunning;

		const uint32_t mClockCycles = 4194304;
		const uint32_t mMachineCycle = 1048576;

		uint64_t mCycleCount;

		CPU& mCPU;
		Memory& mMemory;
		Cartridge& mCartridge;
		Timer& mTimer;
};

#endif // _GAMEBOY_H_