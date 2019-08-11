#ifndef _CPU_H_
#define _CPU_H_

#include "registers.hpp"

class CPU
{
public:
	CPU();

protected:
	// normal 8-bit registers. Can be paired.
	ByteRegister mRegisterA;
	ByteRegister mRegisterB;
	ByteRegister mRegisterC;
	ByteRegister mRegisterD;
	ByteRegister mRegisterE;
	ByteRegister mRegisterG;
	ByteRegister mRegisterH;
	ByteRegister mRegisterL;

	// Flag register. Can be paired.
	FlagRegister mRegisterF; 

	// Paired sets of 8-bit registers, for 16-bits.
	PairedByteRegister mRegisterAF;
	PairedByteRegister mRegisterBC;
	PairedByteRegister mRegisterDE;
	PairedByteRegister mRegisterHL;

	// 16 bit stack pointer and program counter.
	TwoByteRegister mStackPointer;
	TwoByteRegister mProgramCounter;

};

#endif // _CPU_H_