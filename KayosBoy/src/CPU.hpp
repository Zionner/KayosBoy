#ifndef _CPU_H_
#define _CPU_H_

#include "registers.hpp"

class CPU
{
public:

protected:
	ByteRegister a, b, c, d, e, g, h, l; // normal 8-bit registers. Can be paired.
	FlagRegister f; // Flag register. Can be paired.
	PairedByteRegister AF, BC, DE, HL; // Paired sets of 8-bit registers, for 16-bits.
	TwoByteRegister sp, pc; // 16 bit stack pointer and program counter.

};

#endif // _CPU_H_