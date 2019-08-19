#ifndef _TIMER_H_
#define _TIMER_H_

#include "memory.hpp"
#include <iostream>
#include <fstream>

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

	Memory& mMemory;
};

#endif // _TIMER_H_