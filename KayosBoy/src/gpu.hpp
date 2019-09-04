#ifndef _GPU_H_
#define _GPU_H_

#include "memory.hpp"

class GPU
{
public:
	GPU(Memory& mem);

	void Tick(uint64_t elapsedTicks);

private:
	Memory& mMemory;
};

#endif // _GPU_H_