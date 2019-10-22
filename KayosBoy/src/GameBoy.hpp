#ifndef _GAMEBOY_H_
#define _GAMEBOY_H_

#include "CPU.hpp"
#include "Cartridge.hpp"
#include "timer.hpp"
#include "gpu.hpp"

class GameBoy
{
	public:
		GameBoy(CPU& gameboyCPU, Memory& gameboyMemory, Cartridge& cart, Timer& timer, GPU& gpu);

		void Run();

	protected:
		void Tick();

		bool mKeepRunning;

		const uint32_t mClockCycles = 4194304;
		const uint32_t mMachineCycle = 1048576;

		uint64_t mCycleCount;
		uint64_t mFrameCount;

		CPU& mCPU;
		Memory& mMemory;
		Cartridge& mCartridge;
		Timer& mTimer;
		GPU& mGPU;
};

#endif // _GAMEBOY_H_