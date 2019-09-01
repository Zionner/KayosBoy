#ifndef _TIMER_H_
#define _TIMER_H_

#include "memory.hpp"
#include <iostream>
#include <fstream>

enum TimerRegisterAddresses : uint16_t
{
	TRA_Divider = 0xFF04,
	TRA_TimerCounter = 0xFF05,
	TRA_TimerModulo = 0xFF06,
	TRA_TimerControl = 0xFF07
};

enum TimerFrequencyDivider : uint8_t
{
	TFD_4096 = 0x00,
	TFD_16386 = 0x01,
	TFD_65536 = 0x02,
	TFD_262144 = 0x03
};

class Timer
{
public:
	Timer(Memory& mem);
	void Tick(uint64_t elapsedCycles);

protected:
	void SetDividerRegister(uint8_t val);
	void SetTimerCounter(uint8_t val);
	void SetTimerModulo(uint8_t val);
	void SetTimerControl(uint8_t val);

	uint8_t GetDividerRegister();
	uint8_t GetTimerCounter();
	uint8_t GetTimerModulo();
	uint8_t GetTimerControl();
	uint64_t mCycleCounter;

	Memory& mMemory;

	bool mIsTimerEnabled = false;
	TimerFrequencyDivider mFrequencyDividerMode;
	TimerFrequencyDivider mLastFrequencyDividerMode;
};

#endif // _TIMER_H_