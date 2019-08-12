#ifndef _CPU_H_
#define _CPU_H_

#include "registers.hpp"

class CPU
{
public:
	CPU();

protected:
	// normal 8-bit registers. Can be paired.
	ByteRegister mRegisterA; // Accumulator Register
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
	PairedByteRegister mRegisterHL; // Indirect Memory accessor

	// 16 bit stack pointer and program counter.
	TwoByteRegister mStackPointer;
	TwoByteRegister mProgramCounter;

	// Instructions
	// ADC
	void ADC(); // ADC value pointed to from PC register.
	void ADC(uint8_t val);
	void ADC(ByteRegister& val);
	void ADC(KayosBoyPtr& ptrToVal);

	// ADD
	void ADD(); // ADD value pointed to from PC register.
	void ADD_SP(); // ADD value pointed to from PC register to SP.
	void ADD(uint8_t val);
	void ADD(uint16_t val);
	void ADD(ByteRegister& val);
	void ADD(TwoByteRegister& val);
	void ADD(PairedByteRegister& val);
	void ADD(KayosBoyPtr& ptrToVal);

	// AND
	void AND(); // AND value pointed to from PC register.
	void AND(uint8_t val);
	void AND(ByteRegister& val);
	void AND(KayosBoyPtr& ptrToVal);

	// CALL
	void CALL();
	void CALL(uint8_t flagCondition);

	// CFF
	void CFF();

	// CPL
	void CPL();

	// DAA
	void DAA();

	// DEC
	void DEC(ByteRegister& val);
	void DEC(TwoByteRegister& val);
	void DEC(PairedByteRegister& val);
	void DEC(KayosBoyPtr& ptrToVal);

	// DI
	void DI(); // Disable Interrupts

	// EI
	void EI(); // Enable Interrupts

	// CP
	void CP(); // CP value pointed to from PC register.
	void CP(uint8_t val);
	void CP(ByteRegister& val);
	void CP(KayosBoyPtr& ptrToVal);

	// HALT
	void HALT();

	// INC
	void INC(ByteRegister& val);
	void INC(TwoByteRegister& val);
	void INC(PairedByteRegister& val);
	void INC(KayosBoyPtr& ptrToVal);

	// JP
	void JP();
	void JP(uint8_t flagCondition); // Conditions could be handled via enums. Right now it's being handled by bit comparisons.
	void JP(KayosBoyPtr& ptr);

	// JR
	void JR();
	void JR(uint8_t flagCondition); // Conditions could be handled via enums. Right now it's being handled by bit comparisons.

	// NOP
	void NOP();

	// OR
	void OR(); // OR value pointed to from PC register.
	void OR(uint8_t val);
	void OR(ByteRegister& val);
	void OR(KayosBoyPtr& ptrToVal);

	// POP
	void POP(PairedByteRegister& val);

	// PUSH
	void PUSH(PairedByteRegister& val);

	// RST
	void RST(uint8_t offset);

	// SCF
	void SCF();

	// STOP
	void STOP();

	// SUB
	void SUB(); // SUB value pointed to from PC register.
	void SUB(uint8_t val);
	void SUB(ByteRegister& val);
	void SUB(KayosBoyPtr& ptrToVal);

	// SBC
	void SBC(); // SBC value pointed to from PC register.
	void SBC(uint8_t val);
	void SBC(ByteRegister& val);
	void SBC(KayosBoyPtr& ptrToVal);

	// XOR
	void XOR(); // XOR value pointed to from PC register.
	void XOR(uint8_t val);
	void XOR(ByteRegister& val);
	void XOR(KayosBoyPtr& ptrToVal);
};

#endif // _CPU_H_