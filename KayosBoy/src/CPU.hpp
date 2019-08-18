#ifndef _CPU_H_
#define _CPU_H_

#include "memory.hpp"

enum Condition : uint8_t
{
	NotZero,
	Zero,
	NotCarry,
	Carry
};

class CPU
{
public:
	CPU(Memory& mem);

protected:
	bool mIsInterruptsEnabled;

	Memory& mMemory;

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

	uint64_t mTickElapsedCycles;

	uint64_t Tick();

	uint8_t ReadByteFromProgramCounter();
	uint16_t ReadTwoBytesFromProgramCounter();
	KayosBoyPtr ReadAddressFromProgramCounter();

	bool IsCPUInCondition(Condition condition);

	void PushOntoStackPointer(uint16_t val);
	void PushOntoStackPointer(PairedByteRegister& reg);
	void PushOntoStackPointer(TwoByteRegister& reg);
	void PopFromStackPointer(PairedByteRegister& reg);
	void PopFromStackPointer(TwoByteRegister& reg);

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

	// BIT
	void BIT(uint8_t bit, ByteRegister& registerToTest);
	void BIT(uint8_t bit, KayosBoyPtr& addressToByteToTest);

	// CALL
	void CALL();
	void CALL(Condition flagCondition);

	// CFF
	void CCF();

	// CPL
	void CPL();

	// CP
	void CP(); // CP value pointed to from PC register.
	void CP(uint8_t val);
	void CP(ByteRegister& val);
	void CP(KayosBoyPtr& ptrToVal);

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

	// HALT
	void HALT();

	// INC
	void INC(ByteRegister& val);
	void INC(TwoByteRegister& val);
	void INC(PairedByteRegister& val);
	void INC(KayosBoyPtr& ptrToVal);

	// JP
	void JP();
	void JP(Condition flagCondition);
	void JP(KayosBoyPtr& ptr);

	// JR
	void JR();
	void JR(Condition flagCondition);

	// LD
	void LD_PC(ByteRegister& registerToSet);
	void LD_PC(KayosBoyPtr& ptrToSet);
	void LD_PC(PairedByteRegister& val);
	void LD_PC(TwoByteRegister& registerToSet);
	void LD_PCAddress(ByteRegister& registerToSet);
	void LD_WriteToPCAddress(ByteRegister& registerToSet);
	void LD_WriteToPCAddress(TwoByteRegister& registerToSet);
	void LD(ByteRegister& registerToSet, ByteRegister& val);
	void LD(ByteRegister& registerToSet, KayosBoyPtr& val);
	void LD(TwoByteRegister& registerToSet, PairedByteRegister& val);
	void LD(KayosBoyPtr& ptrToSet, ByteRegister& val);
	void LD(KayosBoyPtr& ptrToSet, TwoByteRegister& val);

	// LDD
	void LDD(ByteRegister& registerToSet, KayosBoyPtr& val);
	void LDD(KayosBoyPtr& ptrToSet, ByteRegister& val);

	// LDH
	void LDH_A();
	void LDH_PC();
	void LDH_C();
	void LDH_CAddr_A();

	// LDHL
	void LDHL();

	// LDI
	void LDI(ByteRegister& registerToSet, KayosBoyPtr& val);
	void LDI(KayosBoyPtr& addressToSet, ByteRegister& val);

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

	// RES
	void RES(uint8_t bit, ByteRegister& registerToReset);
	void RES(uint8_t bit, KayosBoyPtr& addressToByteToReset);

	// RET
	void RET();
	void RET(Condition flagCondition);

	// RETI
	void RETI();

	// RLA
	void RLA();

	// RLCA
	void RLCA();

	// RLC
	void RLC(ByteRegister& registerToRotate);
	void RLC(KayosBoyPtr& addressToByteToRotate);

	// RL
	void RL(ByteRegister& registerToRotate);
	void RL(KayosBoyPtr& addressToByteToRotate);

	// RRA
	void RRA();

	// RRCA
	void RRCA();

	// RRC
	void RRC(ByteRegister& registerToRotate);
	void RRC(KayosBoyPtr& addressToByteToRotate);

	// RR
	void RR(ByteRegister& registerToRotate);
	void RR(KayosBoyPtr& addressToByteToRotate);

	// RST
	void RST(uint8_t offset);

	// SBC
	void SBC(); // SBC value pointed to from PC register.
	void SBC(uint8_t val);
	void SBC(ByteRegister& val);
	void SBC(KayosBoyPtr& ptrToVal);

	// SCF
	void SCF();

	// SET
	void SET(uint8_t bit, ByteRegister& registerToSet);
	void SET(uint8_t bit, KayosBoyPtr& addressToByteToSet);

	// SLA
	void SLA(ByteRegister& registerToShift);
	void SLA(KayosBoyPtr& addressToByteToShift);

	// SRA
	void SRA(ByteRegister& registerToShift);
	void SRA(KayosBoyPtr& addressToByteToShift);

	// SRL
	void SRL(ByteRegister& registerToShift);
	void SRL(KayosBoyPtr& addressToByteToShift);

	// STOP
	void STOP();

	// SUB
	void SUB(); // SUB value pointed to from PC register.
	void SUB(uint8_t val);
	void SUB(ByteRegister& val);
	void SUB(KayosBoyPtr& ptrToVal);

	// SWAP
	void SWAP(ByteRegister& registerToSwap);
	void SWAP(KayosBoyPtr& addressToByteToSwap);

	// XOR
	void XOR(); // XOR value pointed to from PC register.
	void XOR(uint8_t val);
	void XOR(ByteRegister& val);
	void XOR(KayosBoyPtr& ptrToVal);

	// OPCODES 0X
	void _00();
	void _01();
	void _02();
	void _03();
	void _04();
	void _05();
	void _06();
	void _07();
	void _08();
	void _09();
	void _0A();
	void _0B();
	void _0C();
	void _0D();
	void _0E();
	void _0F();

	// OPCODES 1X
	void _10();
	void _11();
	void _12();
	void _13();
	void _14();
	void _15();
	void _16();
	void _17();
	void _18();
	void _19();
	void _1A();
	void _1B();
	void _1C();
	void _1D();
	void _1E();
	void _1F();

	// OPCODES 2X
	void _20();
	void _21();
	void _22();
	void _23();
	void _24();
	void _25();
	void _26();
	void _27();
	void _28();
	void _29();
	void _2A();
	void _2B();
	void _2C();
	void _2D();
	void _2E();
	void _2F();

	// OPCODES 3X
	void _30();
	void _31();
	void _32();
	void _33();
	void _34();
	void _35();
	void _36();
	void _37();
	void _38();
	void _39();
	void _3A();
	void _3B();
	void _3C();
	void _3D();
	void _3E();
	void _3F();

	// OPCODES 4X
	void _40();
	void _41();
	void _42();
	void _43();
	void _44();
	void _45();
	void _46();
	void _47();
	void _48();
	void _49();
	void _4A();
	void _4B();
	void _4C();
	void _4D();
	void _4E();
	void _4F();

	// OPCODES 5X
	void _50();
	void _51();
	void _52();
	void _53();
	void _54();
	void _55();
	void _56();
	void _57();
	void _58();
	void _59();
	void _5A();
	void _5B();
	void _5C();
	void _5D();
	void _5E();
	void _5F();

	// OPCODES 6X
	void _60();
	void _61();
	void _62();
	void _63();
	void _64();
	void _65();
	void _66();
	void _67();
	void _68();
	void _69();
	void _6A();
	void _6B();
	void _6C();
	void _6D();
	void _6E();
	void _6F();

	// OPCODES 7X
	void _70();
	void _71();
	void _72();
	void _73();
	void _74();
	void _75();
	void _76();
	void _77();
	void _78();
	void _79();
	void _7A();
	void _7B();
	void _7C();
	void _7D();
	void _7E();
	void _7F();

	// OPCODES 8X
	void _80();
	void _81();
	void _82();
	void _83();
	void _84();
	void _85();
	void _86();
	void _87();
	void _88();
	void _89();
	void _8A();
	void _8B();
	void _8C();
	void _8D();
	void _8E();
	void _8F();

	// OPCODES 9X
	void _90();
	void _91();
	void _92();
	void _93();
	void _94();
	void _95();
	void _96();
	void _97();
	void _98();
	void _99();
	void _9A();
	void _9B();
	void _9C();
	void _9D();
	void _9E();
	void _9F();

	// OPCODES AX
	void _A0();
	void _A1();
	void _A2();
	void _A3();
	void _A4();
	void _A5();
	void _A6();
	void _A7();
	void _A8();
	void _A9();
	void _AA();
	void _AB();
	void _AC();
	void _AD();
	void _AE();
	void _AF();

	// OPCODES BX
	void _B0();
	void _B1();
	void _B2();
	void _B3();
	void _B4();
	void _B5();
	void _B6();
	void _B7();
	void _B8();
	void _B9();
	void _BA();
	void _BB();
	void _BC();
	void _BD();
	void _BE();
	void _BF();

	// OPCODES CX
	void _C0();
	void _C1();
	void _C2();
	void _C3();
	void _C4();
	void _C5();
	void _C6();
	void _C7();
	void _C8();
	void _C9();
	void _CA();
	void _CB();
	void _CC();
	void _CD();
	void _CE();
	void _CF();

	// OPCODES DX
	void _D0();
	void _D1();
	void _D2();
	void _D3();
	void _D4();
	void _D5();
	void _D6();
	void _D7();
	void _D8();
	void _D9();
	void _DA();
	void _DB();
	void _DC();
	void _DD();
	void _DE();
	void _DF();

	// OPCODES EX
	void _E0();
	void _E1();
	void _E2();
	void _E3();
	void _E4();
	void _E5();
	void _E6();
	void _E7();
	void _E8();
	void _E9();
	void _EA();
	void _EB();
	void _EC();
	void _ED();
	void _EE();
	void _EF();

	// OPCODES FX
	void _F0();
	void _F1();
	void _F2();
	void _F3();
	void _F4();
	void _F5();
	void _F6();
	void _F7();
	void _F8();
	void _F9();
	void _FA();
	void _FB();
	void _FC();
	void _FD();
	void _FE();
	void _FF();

	// OPCODES 0X
	void _CB00();
	void _CB01();
	void _CB02();
	void _CB03();
	void _CB04();
	void _CB05();
	void _CB06();
	void _CB07();
	void _CB08();
	void _CB09();
	void _CB0A();
	void _CB0B();
	void _CB0C();
	void _CB0D();
	void _CB0E();
	void _CB0F();
		  
	// OPCODES 1X
	void _CB10();
	void _CB11();
	void _CB12();
	void _CB13();
	void _CB14();
	void _CB15();
	void _CB16();
	void _CB17();
	void _CB18();
	void _CB19();
	void _CB1A();
	void _CB1B();
	void _CB1C();
	void _CB1D();
	void _CB1E();
	void _CB1F();
		  
	// OPCODES 2X
	void _CB20();
	void _CB21();
	void _CB22();
	void _CB23();
	void _CB24();
	void _CB25();
	void _CB26();
	void _CB27();
	void _CB28();
	void _CB29();
	void _CB2A();
	void _CB2B();
	void _CB2C();
	void _CB2D();
	void _CB2E();
	void _CB2F();
		  
	// OPCODES 3X
	void _CB30();
	void _CB31();
	void _CB32();
	void _CB33();
	void _CB34();
	void _CB35();
	void _CB36();
	void _CB37();
	void _CB38();
	void _CB39();
	void _CB3A();
	void _CB3B();
	void _CB3C();
	void _CB3D();
	void _CB3E();
	void _CB3F();
		  
	// OPCODES 4X
	void _CB40();
	void _CB41();
	void _CB42();
	void _CB43();
	void _CB44();
	void _CB45();
	void _CB46();
	void _CB47();
	void _CB48();
	void _CB49();
	void _CB4A();
	void _CB4B();
	void _CB4C();
	void _CB4D();
	void _CB4E();
	void _CB4F();
		  
	// OPCODES 5X
	void _CB50();
	void _CB51();
	void _CB52();
	void _CB53();
	void _CB54();
	void _CB55();
	void _CB56();
	void _CB57();
	void _CB58();
	void _CB59();
	void _CB5A();
	void _CB5B();
	void _CB5C();
	void _CB5D();
	void _CB5E();
	void _CB5F();
		  
	// OPCODES 6X
	void _CB60();
	void _CB61();
	void _CB62();
	void _CB63();
	void _CB64();
	void _CB65();
	void _CB66();
	void _CB67();
	void _CB68();
	void _CB69();
	void _CB6A();
	void _CB6B();
	void _CB6C();
	void _CB6D();
	void _CB6E();
	void _CB6F();
		  
	// OPCODES 7X
	void _CB70();
	void _CB71();
	void _CB72();
	void _CB73();
	void _CB74();
	void _CB75();
	void _CB76();
	void _CB77();
	void _CB78();
	void _CB79();
	void _CB7A();
	void _CB7B();
	void _CB7C();
	void _CB7D();
	void _CB7E();
	void _CB7F();
		  
	// OPCODES 8X
	void _CB80();
	void _CB81();
	void _CB82();
	void _CB83();
	void _CB84();
	void _CB85();
	void _CB86();
	void _CB87();
	void _CB88();
	void _CB89();
	void _CB8A();
	void _CB8B();
	void _CB8C();
	void _CB8D();
	void _CB8E();
	void _CB8F();
		  
	// OPCODES 9X
	void _CB90();
	void _CB91();
	void _CB92();
	void _CB93();
	void _CB94();
	void _CB95();
	void _CB96();
	void _CB97();
	void _CB98();
	void _CB99();
	void _CB9A();
	void _CB9B();
	void _CB9C();
	void _CB9D();
	void _CB9E();
	void _CB9F();
		  
	// OPCODES AX
	void _CBA0();
	void _CBA1();
	void _CBA2();
	void _CBA3();
	void _CBA4();
	void _CBA5();
	void _CBA6();
	void _CBA7();
	void _CBA8();
	void _CBA9();
	void _CBAA();
	void _CBAB();
	void _CBAC();
	void _CBAD();
	void _CBAE();
	void _CBAF();
		  
	// OPCODES BX
	void _CBB0();
	void _CBB1();
	void _CBB2();
	void _CBB3();
	void _CBB4();
	void _CBB5();
	void _CBB6();
	void _CBB7();
	void _CBB8();
	void _CBB9();
	void _CBBA();
	void _CBBB();
	void _CBBC();
	void _CBBD();
	void _CBBE();
	void _CBBF();
		  
	// OPCODES CX
	void _CBC0();
	void _CBC1();
	void _CBC2();
	void _CBC3();
	void _CBC4();
	void _CBC5();
	void _CBC6();
	void _CBC7();
	void _CBC8();
	void _CBC9();
	void _CBCA();
	void _CBCB();
	void _CBCC();
	void _CBCD();
	void _CBCE();
	void _CBCF();
		  
	// OPCODES DX
	void _CBD0();
	void _CBD1();
	void _CBD2();
	void _CBD3();
	void _CBD4();
	void _CBD5();
	void _CBD6();
	void _CBD7();
	void _CBD8();
	void _CBD9();
	void _CBDA();
	void _CBDB();
	void _CBDC();
	void _CBDD();
	void _CBDE();
	void _CBDF();
		  
	// OPCODES EX
	void _CBE0();
	void _CBE1();
	void _CBE2();
	void _CBE3();
	void _CBE4();
	void _CBE5();
	void _CBE6();
	void _CBE7();
	void _CBE8();
	void _CBE9();
	void _CBEA();
	void _CBEB();
	void _CBEC();
	void _CBED();
	void _CBEE();
	void _CBEF();
		  
	// OPCODES FX
	void _CBF0();
	void _CBF1();
	void _CBF2();
	void _CBF3();
	void _CBF4();
	void _CBF5();
	void _CBF6();
	void _CBF7();
	void _CBF8();
	void _CBF9();
	void _CBFA();
	void _CBFB();
	void _CBFC();
	void _CBFD();
	void _CBFE();
	void _CBFF();
};

#endif // _CPU_H_