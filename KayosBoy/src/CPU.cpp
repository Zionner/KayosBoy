#include "CPU.hpp"

CPU::CPU() :
	mRegisterAF(mRegisterA, mRegisterF),
	mRegisterBC(mRegisterB, mRegisterC),
	mRegisterDE(mRegisterD, mRegisterE),
	mRegisterHL(mRegisterH, mRegisterL)
{

}

uint64_t CPU::Tick()
{
	return 0;
}

// ADC
void CPU::ADC()
{

}

void CPU::ADC(uint8_t val)
{

}

void CPU::ADC(ByteRegister& val)
{

}

void CPU::ADC(KayosBoyPtr& ptrToVal)
{

}

// ADD
void CPU::ADD()
{

}

void CPU::ADD_SP()
{

}

void CPU::ADD(uint8_t val)
{

}

void CPU::ADD(uint16_t val)
{

}

void CPU::ADD(ByteRegister& val)
{

}

void CPU::ADD(TwoByteRegister& val)
{

}

void CPU::ADD(PairedByteRegister& val)
{

}

void CPU::ADD(KayosBoyPtr& ptrToVal)
{

}

// AND
void CPU::AND()
{

}

void CPU::AND(uint8_t val)
{

}

void CPU::AND(ByteRegister& val)
{

}

void CPU::AND(KayosBoyPtr& ptrToVal)
{

}

// BIT
void CPU::BIT(uint8_t bit, ByteRegister& registerToTest)
{

}

void CPU::BIT(uint8_t bit, KayosBoyPtr& addressToByteToTest)
{

}

// CALL
void CPU::CALL()
{

}

void CPU::CALL(Condition flagCondition)
{

}

// CCF
void CPU::CCF()
{

}

// CPL
void CPU::CPL()
{

}

// DAA
void CPU::DAA()
{

}

// DEC
void CPU::DEC(ByteRegister& val)
{

}

void CPU::DEC(TwoByteRegister& val)
{

}

void CPU::DEC(PairedByteRegister& val)
{

}

void CPU::DEC(KayosBoyPtr& ptrToVal)
{

}

// DI
void CPU::DI()
{

}

// EI
void CPU::EI()
{

}

// CP
void CPU::CP()
{

}

void CPU::CP(uint8_t val)
{

}

void CPU::CP(ByteRegister& val)
{

}

void CPU::CP(KayosBoyPtr& ptrToVal)
{

}

// HALT
void CPU::HALT()
{

}

// INC
void CPU::INC(ByteRegister& val)
{

}

void CPU::INC(TwoByteRegister& val)
{

}

void CPU::INC(PairedByteRegister& val)
{

}

void CPU::INC(KayosBoyPtr& ptrToVal)
{

}

// JP
void CPU::JP()
{

}

void CPU::JP(Condition flagCondition)
{

}

void CPU::JP(KayosBoyPtr& ptr)
{

}

// JR
void CPU::JR()
{

}

void CPU::JR(Condition flagCondition)
{

}

// LD
void CPU::LD_PC(ByteRegister& registerToSet)
{

}

void CPU::LD_PC(KayosBoyPtr& ptrToSet)
{

}

void CPU::LD_PC(PairedByteRegister& val)
{

}

void CPU::LD_PC(TwoByteRegister& registerToSet)
{

}

void CPU::LD_PCAddress(ByteRegister& registerToSet)
{

}

void CPU::LD_WriteToPCAddress(ByteRegister& registerToSet)
{

}

void CPU::LD_WriteToPCAddress(TwoByteRegister& registerToSet)
{

}

void CPU::LD(ByteRegister& registerToSet, ByteRegister& val)
{

}

void CPU::LD(ByteRegister& registerToSet, KayosBoyPtr& val)
{

}

void CPU::LD(TwoByteRegister& registerToSet, PairedByteRegister& val)
{

}

void CPU::LD(KayosBoyPtr& ptrToSet, ByteRegister& val)
{

}

void CPU::LD(KayosBoyPtr& ptrToSet, TwoByteRegister& val)
{

}

// LDD
void CPU::LDD(ByteRegister& registerToSet, KayosBoyPtr& val)
{

}

void CPU::LDD(KayosBoyPtr& ptrToSet, ByteRegister& val)
{

}

// LDH
void CPU::LDH_A()
{

}

void CPU::LDH_PC()
{

}

void CPU::LDH_C()
{

}

void CPU::LDH_CAddr_A()
{

}

// LDHL
void CPU::LDHL()
{

}

// LDI
void CPU::LDI(ByteRegister& registerToSet, KayosBoyPtr& val)
{

}

void CPU::LDI(KayosBoyPtr& addressToSet, ByteRegister& val)
{

}

// NOP
void CPU::NOP()
{

}

// OR
void CPU::OR()
{

}

void CPU::OR(uint8_t val)
{

}

void CPU::OR(ByteRegister& val)
{

}

void CPU::OR(KayosBoyPtr& ptrToVal)
{

}

// POP
void CPU::POP(PairedByteRegister& val)
{

}

// PUSH
void CPU::PUSH(PairedByteRegister& val)
{

}

// RES
void CPU::RES(uint8_t bit, ByteRegister& registerToReset)
{

}

void CPU::RES(uint8_t bit, KayosBoyPtr& addressToByteToReset)
{

}

// RET
void CPU::RET()
{

}

void CPU::RET(Condition flagCondition)
{

}

// RETI
void CPU::RETI()
{

}

// RLA
void CPU::RLA()
{

}

// RLCA
void CPU::RLCA()
{

}

// RLC
void CPU::RLC(ByteRegister& registerToRotate)
{

}

void CPU::RLC(KayosBoyPtr& addressToByteToRotate)
{

}

// RL
void CPU::RL(ByteRegister& registerToRotate)
{

}

void CPU::RL(KayosBoyPtr& addressToByteToRotate)
{

}

// RRA
void CPU::RRA()
{

}

// RRCA
void CPU::RRCA()
{

}

// RRC
void CPU::RRC(ByteRegister& registerToRotate)
{

}

void CPU::RRC(KayosBoyPtr& addressToByteToRotate)
{

}

// RR
void CPU::RR(ByteRegister& registerToRotate)
{

}

void CPU::RR(KayosBoyPtr& addressToByteToRotate)
{

}

// RST
void CPU::RST(uint8_t offset)
{

}

// SBC
void CPU::SBC()
{

}

void CPU::SBC(uint8_t val)
{

}

void CPU::SBC(ByteRegister& val)
{

}

void CPU::SBC(KayosBoyPtr& ptrToVal)
{

}

// SCF
void CPU::SCF()
{

}

// SET
void CPU::SET(uint8_t bit, ByteRegister& registerToSet)
{

}

void CPU::SET(uint8_t bit, KayosBoyPtr& addressToByteToSet)
{

}

// SLA
void CPU::SLA(ByteRegister& registerToShift)
{

}

void CPU::SLA(KayosBoyPtr& addressToByteToShift)
{

}

// SRA
void CPU::SRA(ByteRegister& registerToShift)
{

}

void CPU::SRA(KayosBoyPtr& addressToByteToShift)
{

}

// SRL
void CPU::SRL(ByteRegister& registerToShift)
{

}

void CPU::SRL(KayosBoyPtr& addressToByteToShift)
{

}

// SWAP
void CPU::SWAP(ByteRegister& registerToSwap)
{

}

void CPU::SWAP(KayosBoyPtr& addressToByteToSwap)
{

}

// STOP
void CPU::STOP()
{

}

// SUB
void CPU::SUB()
{

}

void CPU::SUB(uint8_t val)
{

}

void CPU::SUB(ByteRegister& val)
{

}

void CPU::SUB(KayosBoyPtr& ptrToVal)
{

}

// XOR
void CPU::XOR()
{

}

void CPU::XOR(uint8_t val)
{

}

void CPU::XOR(ByteRegister& val)
{

}

void CPU::XOR(KayosBoyPtr& ptrToVal)
{

}

// OPCODES 0X
void CPU::_00()
{
	NOP();
}

void CPU::_01()
{
	LD_PC(mRegisterBC);
}

void CPU::_02()
{
	LD(mRegisterBC.RegisterAsAddress(), mRegisterA);
}

void CPU::_03()
{
	INC(mRegisterBC);
}

void CPU::_04()
{
	INC(mRegisterB);
}

void CPU::_05()
{
	DEC(mRegisterB);
}

void CPU::_06()
{
	LD_PC(mRegisterB);
}

void CPU::_07()
{
	RLCA();
}

void CPU::_08()
{
	LD_WriteToPCAddress(mStackPointer);
}

void CPU::_09()
{
	ADD(mRegisterBC);
}

void CPU::_0A()
{
	LD(mRegisterA, mRegisterBC.RegisterAsAddress());
}

void CPU::_0B()
{
	DEC(mRegisterBC);
}

void CPU::_0C()
{
	INC(mRegisterC);
}

void CPU::_0D()
{
	DEC(mRegisterC);
}

void CPU::_0E()
{
	LD_PC(mRegisterC);
}

void CPU::_0F()
{
	RRCA();
}


// OPCODES 1X
void CPU::_10()
{
	STOP();
}

void CPU::_11()
{
	LD_PC(mRegisterDE);
}

void CPU::_12()
{
	LD(mRegisterDE.RegisterAsAddress(), mRegisterA);
}

void CPU::_13()
{
	INC(mRegisterDE);
}

void CPU::_14()
{
	INC(mRegisterD);
}

void CPU::_15()
{
	DEC(mRegisterD);
}

void CPU::_16()
{
	LD_PC(mRegisterD);
}

void CPU::_17()
{
	RLA();
}

void CPU::_18()
{
	JR();
}

void CPU::_19()
{
	ADD(mRegisterDE);
}

void CPU::_1A()
{
	LD(mRegisterA, mRegisterDE.RegisterAsAddress());
}

void CPU::_1B()
{
	DEC(mRegisterDE);
}

void CPU::_1C()
{
	INC(mRegisterE);
}

void CPU::_1D()
{
	DEC(mRegisterE);
}

void CPU::_1E()
{
	LD_PC(mRegisterE);
}

void CPU::_1F()
{
	RRA();
}


// OPCODES 2X
void CPU::_20()
{
	JR(NotZero);
}

void CPU::_21()
{
	LD_PC(mRegisterDE);
}

void CPU::_22()
{
	LD(mRegisterDE.RegisterAsAddress(), mRegisterA);
}

void CPU::_23()
{
	INC(mRegisterDE);
}

void CPU::_24()
{
	INC(mRegisterD);
}

void CPU::_25()
{
	DEC(mRegisterH);
}

void CPU::_26()
{
	LD_PC(mRegisterH);
}

void CPU::_27()
{
	DAA();
}

void CPU::_28()
{
	JR(Zero);
}

void CPU::_29()
{
	ADD(mRegisterHL);
}

void CPU::_2A()
{
	LDI(mRegisterA, mRegisterHL.RegisterAsAddress());
}

void CPU::_2B()
{
	DEC(mRegisterHL);
}

void CPU::_2C()
{
	INC(mRegisterL);
}

void CPU::_2D()
{
	DEC(mRegisterL);
}

void CPU::_2E()
{
	LD_PC(mRegisterL);
}

void CPU::_2F()
{
	CPL();
}


// OPCODES 3X
void CPU::_30()
{
	JR(NotCarry);
}

void CPU::_31()
{
	LD_PC(mStackPointer);
}

void CPU::_32()
{
	LDD(mRegisterHL.RegisterAsAddress(), mRegisterA);
}

void CPU::_33()
{
	INC(mStackPointer);
}

void CPU::_34()
{
	INC(mRegisterHL.RegisterAsAddress());
}

void CPU::_35()
{
	DEC(mRegisterHL.RegisterAsAddress());
}

void CPU::_36()
{
	LD_PC(mRegisterHL.RegisterAsAddress());
}

void CPU::_37()
{
	SCF();
}

void CPU::_38()
{
	JR(Carry);
}

void CPU::_39()
{
	ADD(mStackPointer);
}

void CPU::_3A()
{
	LDD(mRegisterA, mRegisterHL.RegisterAsAddress());
}

void CPU::_3B()
{
	DEC(mStackPointer);
}

void CPU::_3C()
{
	INC(mRegisterA);
}

void CPU::_3D()
{
	DEC(mRegisterA);
}

void CPU::_3E()
{
	LD_PC(mRegisterA);
}

void CPU::_3F()
{
	CCF();
}


// OPCODES 4X
void CPU::_40()
{
	LD(mRegisterB, mRegisterB);
}

void CPU::_41()
{
	LD(mRegisterB, mRegisterC);
}

void CPU::_42()
{
	LD(mRegisterB, mRegisterD);
}

void CPU::_43()
{
	LD(mRegisterB, mRegisterE);
}

void CPU::_44()
{
	LD(mRegisterB, mRegisterH);
}

void CPU::_45()
{
	LD(mRegisterB, mRegisterL);
}

void CPU::_46()
{
	LD(mRegisterB, mRegisterHL.RegisterAsAddress());
}

void CPU::_47()
{
	LD(mRegisterB, mRegisterA);
}

void CPU::_48()
{
	LD(mRegisterC, mRegisterB);
}

void CPU::_49()
{
	LD(mRegisterC, mRegisterC);
}

void CPU::_4A()
{
	LD(mRegisterC, mRegisterD);
}

void CPU::_4B()
{
	LD(mRegisterC, mRegisterE);
}

void CPU::_4C()
{
	LD(mRegisterC, mRegisterH);
}

void CPU::_4D()
{
	LD(mRegisterC, mRegisterL);
}

void CPU::_4E()
{
	LD(mRegisterC, mRegisterHL.RegisterAsAddress());
}

void CPU::_4F()
{
	LD(mRegisterC, mRegisterA);
}


// OPCODES 5X
void CPU::_50()
{
	LD(mRegisterD, mRegisterB);
}

void CPU::_51()
{
	LD(mRegisterD, mRegisterC);
}

void CPU::_52()
{
	LD(mRegisterD, mRegisterD);
}

void CPU::_53()
{
	LD(mRegisterD, mRegisterE);
}

void CPU::_54()
{
	LD(mRegisterD, mRegisterH);
}

void CPU::_55()
{
	LD(mRegisterD, mRegisterL);
}

void CPU::_56()
{
	LD(mRegisterD, mRegisterHL.RegisterAsAddress());
}

void CPU::_57()
{
	LD(mRegisterD, mRegisterA);
}

void CPU::_58()
{
	LD(mRegisterE, mRegisterB);
}

void CPU::_59()
{
	LD(mRegisterE, mRegisterC);
}

void CPU::_5A()
{
	LD(mRegisterE, mRegisterD);
}

void CPU::_5B()
{
	LD(mRegisterE, mRegisterE);
}

void CPU::_5C()
{
	LD(mRegisterE, mRegisterH);
}

void CPU::_5D()
{
	LD(mRegisterE, mRegisterL);
}

void CPU::_5E()
{
	LD(mRegisterE, mRegisterHL.RegisterAsAddress());
}

void CPU::_5F()
{
	LD(mRegisterE, mRegisterA);
}


// OPCODES 6X
void CPU::_60()
{
	LD(mRegisterH, mRegisterB);
}

void CPU::_61()
{
	LD(mRegisterH, mRegisterC);
}

void CPU::_62()
{
	LD(mRegisterH, mRegisterD);
}

void CPU::_63()
{
	LD(mRegisterH, mRegisterE);
}

void CPU::_64()
{
	LD(mRegisterH, mRegisterH);
}

void CPU::_65()
{
	LD(mRegisterH, mRegisterL);
}

void CPU::_66()
{
	LD(mRegisterH, mRegisterHL.RegisterAsAddress());
}

void CPU::_67()
{
	LD(mRegisterH, mRegisterA);
}

void CPU::_68()
{
	LD(mRegisterL, mRegisterB);
}

void CPU::_69()
{
	LD(mRegisterL, mRegisterC);
}

void CPU::_6A()
{
	LD(mRegisterL, mRegisterD);
}

void CPU::_6B()
{
	LD(mRegisterL, mRegisterE);
}

void CPU::_6C()
{
	LD(mRegisterL, mRegisterH);
}

void CPU::_6D()
{
	LD(mRegisterL, mRegisterL);
}

void CPU::_6E()
{
	LD(mRegisterL, mRegisterHL.RegisterAsAddress());
}

void CPU::_6F()
{
	LD(mRegisterL, mRegisterA);
}


// OPCODES 7X
void CPU::_70()
{
	LD(mRegisterHL.RegisterAsAddress(), mRegisterB);
}

void CPU::_71()
{
	LD(mRegisterHL.RegisterAsAddress(), mRegisterC);
}

void CPU::_72()
{
	LD(mRegisterHL.RegisterAsAddress(), mRegisterD);
}

void CPU::_73()
{
	LD(mRegisterHL.RegisterAsAddress(), mRegisterE);
}

void CPU::_74()
{
	LD(mRegisterHL.RegisterAsAddress(), mRegisterH);
}

void CPU::_75()
{
	LD(mRegisterHL.RegisterAsAddress(), mRegisterL);
}

void CPU::_76()
{
	HALT();
}

void CPU::_77()
{
	LD(mRegisterHL.RegisterAsAddress(), mRegisterA);
}

void CPU::_78()
{
	LD(mRegisterA, mRegisterB);
}

void CPU::_79()
{
	LD(mRegisterA, mRegisterC);
}

void CPU::_7A()
{
	LD(mRegisterA, mRegisterD);
}

void CPU::_7B()
{
	LD(mRegisterA, mRegisterE);
}

void CPU::_7C()
{
	LD(mRegisterA, mRegisterH);
}

void CPU::_7D()
{
	LD(mRegisterA, mRegisterL);
}

void CPU::_7E()
{
	LD(mRegisterA, mRegisterHL.RegisterAsAddress());
}

void CPU::_7F()
{
	LD(mRegisterA, mRegisterA);
}


// OPCODES 8X
void CPU::_80()
{
	ADD(mRegisterB);
}

void CPU::_81()
{
	ADD(mRegisterC);
}

void CPU::_82()
{
	ADD(mRegisterD);
}

void CPU::_83()
{
	ADD(mRegisterE);
}

void CPU::_84()
{
	ADD(mRegisterH);
}

void CPU::_85()
{
	ADD(mRegisterL);
}

void CPU::_86()
{
	ADD(mRegisterHL.RegisterAsAddress());
}

void CPU::_87()
{
	ADD(mRegisterA);
}

void CPU::_88()
{
	ADC(mRegisterB);
}

void CPU::_89()
{
	ADC(mRegisterC);
}

void CPU::_8A()
{
	ADC(mRegisterD);

}

void CPU::_8B()
{
	ADC(mRegisterE);
}

void CPU::_8C()
{
	ADC(mRegisterH);
}

void CPU::_8D()
{
	ADC(mRegisterL);
}

void CPU::_8E()
{
	ADC(mRegisterHL.RegisterAsAddress());
}

void CPU::_8F()
{
	ADC(mRegisterA);
}


// OPCODES 9X
void CPU::_90()
{
	SUB(mRegisterB);
}

void CPU::_91()
{
	SUB(mRegisterC);
}

void CPU::_92()
{
	SUB(mRegisterD);
}

void CPU::_93()
{
	SUB(mRegisterE);
}

void CPU::_94()
{
	SUB(mRegisterH);
}

void CPU::_95()
{
	SUB(mRegisterL);
}

void CPU::_96()
{
	SUB(mRegisterHL.RegisterAsAddress());
}

void CPU::_97()
{
	SUB(mRegisterA);
}

void CPU::_98()
{
	SBC(mRegisterB);
}

void CPU::_99()
{
	SBC(mRegisterC);
}

void CPU::_9A()
{
	SBC(mRegisterD);
}

void CPU::_9B()
{
	SBC(mRegisterE);
}

void CPU::_9C()
{
	SBC(mRegisterH);
}

void CPU::_9D()
{
	SBC(mRegisterL);
}

void CPU::_9E()
{
	SBC(mRegisterHL.RegisterAsAddress());
}

void CPU::_9F()
{
	SBC(mRegisterA);
}


// OPCODES AX
void CPU::_A0()
{
	AND(mRegisterB);
}

void CPU::_A1()
{
	AND(mRegisterC);
}

void CPU::_A2()
{
	AND(mRegisterD);
}

void CPU::_A3()
{
	AND(mRegisterE);
}

void CPU::_A4()
{
	AND(mRegisterH);
}

void CPU::_A5()
{
	AND(mRegisterL);
}

void CPU::_A6()
{
	AND(mRegisterHL.RegisterAsAddress());
}

void CPU::_A7()
{
	AND(mRegisterA);
}

void CPU::_A8()
{
	XOR(mRegisterB);
}

void CPU::_A9()
{
	XOR(mRegisterC);
}

void CPU::_AA()
{
	XOR(mRegisterD);
}

void CPU::_AB()
{
	XOR(mRegisterE);
}

void CPU::_AC()
{
	XOR(mRegisterH);
}

void CPU::_AD()
{
	XOR(mRegisterL);
}

void CPU::_AE()
{
	XOR(mRegisterHL.RegisterAsAddress());
}

void CPU::_AF()
{
	XOR(mRegisterA);
}


// OPCODES BX
void CPU::_B0()
{
	OR(mRegisterB);
}

void CPU::_B1()
{
	OR(mRegisterC);
}

void CPU::_B2()
{
	OR(mRegisterD);
}

void CPU::_B3()
{
	OR(mRegisterE);
}

void CPU::_B4()
{
	OR(mRegisterH);
}

void CPU::_B5()
{
	OR(mRegisterL);
}

void CPU::_B6()
{
	OR(mRegisterHL.RegisterAsAddress());
}

void CPU::_B7()
{
	OR(mRegisterA);
}

void CPU::_B8()
{
	CP(mRegisterB);
}

void CPU::_B9()
{
	CP(mRegisterC);
}

void CPU::_BA()
{
	CP(mRegisterD);
}

void CPU::_BB()
{
	CP(mRegisterE);
}

void CPU::_BC()
{
	CP(mRegisterH);
}

void CPU::_BD()
{
	CP(mRegisterL);
}

void CPU::_BE()
{
	CP(mRegisterHL.RegisterAsAddress());
}

void CPU::_BF()
{
	CP(mRegisterA);
}


// OPCODES CX
void CPU::_C0()
{
	RET(NotZero);
}

void CPU::_C1()
{
	POP(mRegisterBC);
}

void CPU::_C2()
{
	JP(NotZero);
}

void CPU::_C3()
{
	JP();
}

void CPU::_C4()
{
	CALL(NotZero);
}

void CPU::_C5()
{
	PUSH(mRegisterBC);
}

void CPU::_C6()
{
	ADD();
}

void CPU::_C7()
{
	RST(0x00);
}

void CPU::_C8()
{
	RET(Zero);
}

void CPU::_C9()
{
	RET();
}

void CPU::_CA()
{
	JP(Zero);
}

void CPU::_CB()
{
	// PREFIX
}

void CPU::_CC()
{
	CALL(Zero);
}

void CPU::_CD()
{
	CALL();
}

void CPU::_CE()
{
	ADC();
}

void CPU::_CF()
{
	RST(0x08);
}


// OPCODES DX
void CPU::_D0()
{
	RET(NotCarry);
}

void CPU::_D1()
{
	POP(mRegisterDE);
}

void CPU::_D2()
{
	JP(NotCarry);
}

void CPU::_D3()
{
	// ERROR
}

void CPU::_D4()
{
	CALL(NotCarry);
}

void CPU::_D5()
{
	PUSH(mRegisterDE);
}

void CPU::_D6()
{
	SUB();
}

void CPU::_D7()
{
	RST(0x10);
}

void CPU::_D8()
{
	RET(Carry);
}

void CPU::_D9()
{
	RETI();
}

void CPU::_DA()
{
	JP(Carry);
}

void CPU::_DB()
{
	// ERROR
}

void CPU::_DC()
{
	CALL(Carry);
}

void CPU::_DD()
{
	// ERROR
}

void CPU::_DE()
{
	SBC();
}

void CPU::_DF()
{
	RST(0x18);
}


// OPCODES EX
void CPU::_E0()
{
	
}

void CPU::_E1()
{
	POP(mRegisterHL);
}

void CPU::_E2()
{

}

void CPU::_E3()
{
	// ERROR
}

void CPU::_E4()
{
	// ERROR
}

void CPU::_E5()
{
	PUSH(mRegisterHL);
}

void CPU::_E6()
{
	AND();
}

void CPU::_E7()
{
	RST(0x20);
}

void CPU::_E8()
{
	ADD_SP();
}

void CPU::_E9()
{
	JP(mRegisterHL.RegisterAsAddress());
}

void CPU::_EA()
{

}

void CPU::_EB()
{
	// ERROR
}

void CPU::_EC()
{
	// ERROR
}

void CPU::_ED()
{
	// ERROR
}

void CPU::_EE()
{
	XOR();
}

void CPU::_EF()
{
	RST(0x28);
}


// OPCODES FX
void CPU::_F0()
{
	LDH_A();
}

void CPU::_F1()
{
	POP(mRegisterAF);
}

void CPU::_F2()
{
	LDH_CAddr_A();
}

void CPU::_F3()
{
	DI();
}

void CPU::_F4()
{
	// ERROR
}

void CPU::_F5()
{
	PUSH(mRegisterAF);
}

void CPU::_F6()
{
	OR();
}

void CPU::_F7()
{
	RST(0x30);
}

void CPU::_F8()
{
	LDHL();
}

void CPU::_F9()
{
	LD(mStackPointer, mRegisterHL);
}

void CPU::_FA()
{

}

void CPU::_FB()
{
	EI();
}

void CPU::_FC()
{
	// ERROR
}

void CPU::_FD()
{
	// ERROR
}

void CPU::_FE()
{
	CP();
}

void CPU::_FF()
{
	RST(0x38);
}


// OPCODES CB0X
void CPU::_CB00()
{
	RLC(mRegisterB);
}

void CPU::_CB01()
{
	RLC(mRegisterC);
}

void CPU::_CB02()
{
	RLC(mRegisterD);
}

void CPU::_CB03()
{
	RLC(mRegisterE);
}

void CPU::_CB04()
{
	RLC(mRegisterH);
}

void CPU::_CB05()
{
	RLC(mRegisterL);
}

void CPU::_CB06()
{
	RLC(mRegisterHL.RegisterAsAddress());
}

void CPU::_CB07()
{
	RLC(mRegisterA);
}

void CPU::_CB08()
{
	RRC(mRegisterB);
}

void CPU::_CB09()
{
	RRC(mRegisterC);
}

void CPU::_CB0A()
{
	RRC(mRegisterD);
}

void CPU::_CB0B()
{
	RRC(mRegisterE);
}

void CPU::_CB0C()
{
	RRC(mRegisterH);
}

void CPU::_CB0D()
{
	RRC(mRegisterL);
}

void CPU::_CB0E()
{
	RRC(mRegisterHL.RegisterAsAddress());
}

void CPU::_CB0F()
{
	RRC(mRegisterA);
}


// OPCODES CB1X
void CPU::_CB10()
{
	RL(mRegisterB);
}

void CPU::_CB11()
{
	RL(mRegisterC);
}

void CPU::_CB12()
{
	RL(mRegisterD);
}

void CPU::_CB13()
{
	RL(mRegisterE);
}

void CPU::_CB14()
{
	RL(mRegisterH);
}

void CPU::_CB15()
{
	RL(mRegisterL);
}

void CPU::_CB16()
{
	RL(mRegisterHL.RegisterAsAddress());
}

void CPU::_CB17()
{
	RL(mRegisterA);
}

void CPU::_CB18()
{
	RR(mRegisterB);
}

void CPU::_CB19()
{
	RR(mRegisterC);
}

void CPU::_CB1A()
{
	RR(mRegisterD);
}

void CPU::_CB1B()
{
	RR(mRegisterE);
}

void CPU::_CB1C()
{
	RR(mRegisterH);
}

void CPU::_CB1D()
{
	RR(mRegisterL);
}

void CPU::_CB1E()
{
	RR(mRegisterHL.RegisterAsAddress());
}

void CPU::_CB1F()
{
	RR(mRegisterA);
}


// OPCODES CB2X
void CPU::_CB20()
{
	SLA(mRegisterB);
}

void CPU::_CB21()
{
	SLA(mRegisterC);
}

void CPU::_CB22()
{
	SLA(mRegisterD);
}

void CPU::_CB23()
{
	SLA(mRegisterE);
}

void CPU::_CB24()
{
	SLA(mRegisterH);
}

void CPU::_CB25()
{
	SLA(mRegisterL);
}

void CPU::_CB26()
{
	SLA(mRegisterHL.RegisterAsAddress());
}

void CPU::_CB27()
{
	SLA(mRegisterA);
}

void CPU::_CB28()
{
	SRA(mRegisterB);
}

void CPU::_CB29()
{
	SRA(mRegisterC);
}

void CPU::_CB2A()
{
	SRA(mRegisterD);
}

void CPU::_CB2B()
{
	SRA(mRegisterE);
}

void CPU::_CB2C()
{
	SRA(mRegisterH);
}

void CPU::_CB2D()
{
	SRA(mRegisterL);
}

void CPU::_CB2E()
{
	SRA(mRegisterHL.RegisterAsAddress());
}

void CPU::_CB2F()
{
	SRA(mRegisterA);
}


// OPCODES CB3X
void CPU::_CB30()
{
	SWAP(mRegisterB);
}

void CPU::_CB31()
{
	SWAP(mRegisterC);
}

void CPU::_CB32()
{
	SWAP(mRegisterD);
}

void CPU::_CB33()
{
	SWAP(mRegisterE);
}

void CPU::_CB34()
{
	SWAP(mRegisterH);
}

void CPU::_CB35()
{
	SWAP(mRegisterL);
}

void CPU::_CB36()
{
	SWAP(mRegisterHL.RegisterAsAddress());
}

void CPU::_CB37()
{
	SWAP(mRegisterA);
}

void CPU::_CB38()
{
	SRL(mRegisterB);
}

void CPU::_CB39()
{
	SRL(mRegisterC);
}

void CPU::_CB3A()
{
	SRL(mRegisterD);
}

void CPU::_CB3B()
{
	SRL(mRegisterE);
}

void CPU::_CB3C()
{
	SRL(mRegisterH);
}

void CPU::_CB3D()
{
	SRL(mRegisterL);
}

void CPU::_CB3E()
{
	SRL(mRegisterHL.RegisterAsAddress());
}

void CPU::_CB3F()
{
	SRL(mRegisterA);
}


// OPCODES CB4X
void CPU::_CB40()
{
	BIT(0, mRegisterB);
}

void CPU::_CB41()
{
	BIT(0, mRegisterC);
}

void CPU::_CB42()
{
	BIT(0, mRegisterD);
}

void CPU::_CB43()
{
	BIT(0, mRegisterE);
}

void CPU::_CB44()
{
	BIT(0, mRegisterH);
}

void CPU::_CB45()
{
	BIT(0, mRegisterL);
}

void CPU::_CB46()
{
	BIT(0, mRegisterHL.RegisterAsAddress());
}

void CPU::_CB47()
{
	BIT(0, mRegisterA);
}

void CPU::_CB48()
{
	BIT(1, mRegisterB);
}

void CPU::_CB49()
{
	BIT(1, mRegisterC);
}

void CPU::_CB4A()
{
	BIT(1, mRegisterD);
}

void CPU::_CB4B()
{
	BIT(1, mRegisterE);
}

void CPU::_CB4C()
{
	BIT(1, mRegisterH);
}

void CPU::_CB4D()
{
	BIT(1, mRegisterL);
}

void CPU::_CB4E()
{
	BIT(1, mRegisterHL.RegisterAsAddress());
}

void CPU::_CB4F()
{
	BIT(1, mRegisterA);
}


// OPCODES CB5X
void CPU::_CB50()
{
	BIT(2, mRegisterB);
}

void CPU::_CB51()
{
	BIT(2, mRegisterC);
}

void CPU::_CB52()
{
	BIT(2, mRegisterD);
}

void CPU::_CB53()
{
	BIT(2, mRegisterE);
}

void CPU::_CB54()
{
	BIT(2, mRegisterH);
}

void CPU::_CB55()
{
	BIT(2, mRegisterL);
}

void CPU::_CB56()
{
	BIT(2, mRegisterHL.RegisterAsAddress());
}

void CPU::_CB57()
{
	BIT(2, mRegisterA);
}

void CPU::_CB58()
{
	BIT(3, mRegisterB);
}

void CPU::_CB59()
{
	BIT(3, mRegisterC);
}

void CPU::_CB5A()
{
	BIT(3, mRegisterD);
}

void CPU::_CB5B()
{
	BIT(3, mRegisterE);
}

void CPU::_CB5C()
{
	BIT(3, mRegisterH);
}

void CPU::_CB5D()
{
	BIT(3, mRegisterL);
}

void CPU::_CB5E()
{
	BIT(3, mRegisterHL.RegisterAsAddress());
}

void CPU::_CB5F()
{
	BIT(3, mRegisterA);
}


// OPCODES CB6X
void CPU::_CB60()
{
	BIT(4, mRegisterB);
}

void CPU::_CB61()
{
	BIT(4, mRegisterC);
}

void CPU::_CB62()
{
	BIT(4, mRegisterD);
}

void CPU::_CB63()
{
	BIT(4, mRegisterE);
}

void CPU::_CB64()
{
	BIT(4, mRegisterH);
}

void CPU::_CB65()
{
	BIT(4, mRegisterL);
}

void CPU::_CB66()
{
	BIT(4, mRegisterHL.RegisterAsAddress());
}

void CPU::_CB67()
{
	BIT(4, mRegisterA);
}

void CPU::_CB68()
{
	BIT(5, mRegisterB);
}

void CPU::_CB69()
{
	BIT(5, mRegisterC);
}

void CPU::_CB6A()
{
	BIT(5, mRegisterD);
}

void CPU::_CB6B()
{
	BIT(5, mRegisterE);
}

void CPU::_CB6C()
{
	BIT(5, mRegisterH);
}

void CPU::_CB6D()
{
	BIT(5, mRegisterL);
}

void CPU::_CB6E()
{
	BIT(5, mRegisterHL.RegisterAsAddress());
}

void CPU::_CB6F()
{
	BIT(5, mRegisterA);
}


// OPCODES CB7X
void CPU::_CB70()
{
	BIT(6, mRegisterB);
}

void CPU::_CB71()
{
	BIT(6, mRegisterC);
}

void CPU::_CB72()
{
	BIT(6, mRegisterD);
}

void CPU::_CB73()
{
	BIT(6, mRegisterE);
}

void CPU::_CB74()
{
	BIT(6, mRegisterH);
}

void CPU::_CB75()
{
	BIT(6, mRegisterL);
}

void CPU::_CB76()
{
	BIT(6, mRegisterHL.RegisterAsAddress());
}

void CPU::_CB77()
{
	BIT(6, mRegisterA);
}

void CPU::_CB78()
{
	BIT(7, mRegisterB);
}

void CPU::_CB79()
{
	BIT(7, mRegisterC);
}

void CPU::_CB7A()
{
	BIT(7, mRegisterD);
}

void CPU::_CB7B()
{
	BIT(7, mRegisterE);
}

void CPU::_CB7C()
{
	BIT(7, mRegisterH);
}

void CPU::_CB7D()
{
	BIT(7, mRegisterL);
}

void CPU::_CB7E()
{
	BIT(7, mRegisterHL.RegisterAsAddress());
}

void CPU::_CB7F()
{
	BIT(7, mRegisterA);
}


// OPCODES CB8X
void CPU::_CB80()
{
	RES(0, mRegisterB);
}

void CPU::_CB81()
{
	RES(0, mRegisterC);
}

void CPU::_CB82()
{
	RES(0, mRegisterD);
}

void CPU::_CB83()
{
	RES(0, mRegisterE);
}

void CPU::_CB84()
{
	RES(0, mRegisterH);
}

void CPU::_CB85()
{
	RES(0, mRegisterL);
}

void CPU::_CB86()
{
	RES(0, mRegisterHL.RegisterAsAddress());
}

void CPU::_CB87()
{
	RES(0, mRegisterA);
}

void CPU::_CB88()
{
	RES(1, mRegisterB);
}

void CPU::_CB89()
{
	RES(1, mRegisterC);
}

void CPU::_CB8A()
{
	RES(1, mRegisterD);
}

void CPU::_CB8B()
{
	RES(1, mRegisterE);
}

void CPU::_CB8C()
{
	RES(1, mRegisterH);
}

void CPU::_CB8D()
{
	RES(1, mRegisterL);
}

void CPU::_CB8E()
{
	RES(1, mRegisterHL.RegisterAsAddress());
}

void CPU::_CB8F()
{
	RES(1, mRegisterA);
}


// OPCODES CB9X
void CPU::_CB90()
{
	RES(2, mRegisterB);
}

void CPU::_CB91()
{
	RES(2, mRegisterC);
}

void CPU::_CB92()
{
	RES(2, mRegisterD);
}

void CPU::_CB93()
{
	RES(2, mRegisterE);
}

void CPU::_CB94()
{
	RES(2, mRegisterH);
}

void CPU::_CB95()
{
	RES(2, mRegisterL);
}

void CPU::_CB96()
{
	RES(2, mRegisterHL.RegisterAsAddress());
}

void CPU::_CB97()
{
	RES(2, mRegisterA);
}

void CPU::_CB98()
{
	RES(3, mRegisterB);
}

void CPU::_CB99()
{
	RES(3, mRegisterC);
}

void CPU::_CB9A()
{
	RES(3, mRegisterD);
}

void CPU::_CB9B()
{
	RES(3, mRegisterE);
}

void CPU::_CB9C()
{
	RES(3, mRegisterH);
}

void CPU::_CB9D()
{
	RES(3, mRegisterL);
}

void CPU::_CB9E()
{
	RES(3, mRegisterHL.RegisterAsAddress());
}

void CPU::_CB9F()
{
	RES(3, mRegisterA);
}


// OPCODES CBAX
void CPU::_CBA0()
{
	RES(4, mRegisterB);
}

void CPU::_CBA1()
{
	RES(4, mRegisterC);
}

void CPU::_CBA2()
{
	RES(4, mRegisterD);
}

void CPU::_CBA3()
{
	RES(4, mRegisterE);
}

void CPU::_CBA4()
{
	RES(4, mRegisterH);
}

void CPU::_CBA5()
{
	RES(4, mRegisterL);
}

void CPU::_CBA6()
{
	RES(4, mRegisterHL.RegisterAsAddress());
}

void CPU::_CBA7()
{
	RES(4, mRegisterA);
}

void CPU::_CBA8()
{
	RES(5, mRegisterB);
}

void CPU::_CBA9()
{
	RES(5, mRegisterC);
}

void CPU::_CBAA()
{
	RES(5, mRegisterD);
}

void CPU::_CBAB()
{
	RES(5, mRegisterE);
}

void CPU::_CBAC()
{
	RES(5, mRegisterH);
}

void CPU::_CBAD()
{
	RES(5, mRegisterL);
}

void CPU::_CBAE()
{
	RES(5, mRegisterHL.RegisterAsAddress());
}

void CPU::_CBAF()
{
	RES(5, mRegisterA);
}


// OPCODES CBBX
void CPU::_CBB0()
{
	RES(6, mRegisterB);
}

void CPU::_CBB1()
{
	RES(6, mRegisterC);
}

void CPU::_CBB2()
{
	RES(6, mRegisterD);
}

void CPU::_CBB3()
{
	RES(6, mRegisterE);
}

void CPU::_CBB4()
{
	RES(6, mRegisterH);
}

void CPU::_CBB5()
{
	RES(6, mRegisterL);
}

void CPU::_CBB6()
{
	RES(6, mRegisterHL.RegisterAsAddress());
}

void CPU::_CBB7()
{
	RES(6, mRegisterA);
}

void CPU::_CBB8()
{
	RES(7, mRegisterB);
}

void CPU::_CBB9()
{
	RES(7, mRegisterC);
}

void CPU::_CBBA()
{
	RES(7, mRegisterD);
}

void CPU::_CBBB()
{
	RES(7, mRegisterE);
}

void CPU::_CBBC()
{
	RES(7, mRegisterH);
}

void CPU::_CBBD()
{
	RES(7, mRegisterL);
}

void CPU::_CBBE()
{
	RES(7, mRegisterHL.RegisterAsAddress());
}

void CPU::_CBBF()
{
	RES(7, mRegisterA);
}


// OPCODES CBCX
void CPU::_CBC0()
{
	SET(0, mRegisterB);
}

void CPU::_CBC1()
{
	SET(0, mRegisterC);
}

void CPU::_CBC2()
{
	SET(0, mRegisterD);
}

void CPU::_CBC3()
{
	SET(0, mRegisterE);
}

void CPU::_CBC4()
{
	SET(0, mRegisterH);
}

void CPU::_CBC5()
{
	SET(0, mRegisterL);
}

void CPU::_CBC6()
{
	SET(0, mRegisterHL.RegisterAsAddress());
}

void CPU::_CBC7()
{
	SET(0, mRegisterA);
}

void CPU::_CBC8()
{
	SET(1, mRegisterB);
}

void CPU::_CBC9()
{
	SET(1, mRegisterC);
}

void CPU::_CBCA()
{
	SET(1, mRegisterD);
}

void CPU::_CBCB()
{
	SET(1, mRegisterE);
}

void CPU::_CBCC()
{
	SET(1, mRegisterH);
}

void CPU::_CBCD()
{
	SET(1, mRegisterL);
}

void CPU::_CBCE()
{
	SET(1, mRegisterHL.RegisterAsAddress());
}

void CPU::_CBCF()
{
	SET(1, mRegisterA);
}


// OPCODES CBDX
void CPU::_CBD0()
{
	SET(2, mRegisterB);
}

void CPU::_CBD1()
{
	SET(2, mRegisterC);
}

void CPU::_CBD2()
{
	SET(2, mRegisterD);
}

void CPU::_CBD3()
{
	SET(2, mRegisterE);
}

void CPU::_CBD4()
{
	SET(2, mRegisterH);
}

void CPU::_CBD5()
{
	SET(2, mRegisterL);
}

void CPU::_CBD6()
{
	SET(2, mRegisterHL.RegisterAsAddress());
}

void CPU::_CBD7()
{
	SET(2, mRegisterA);
}

void CPU::_CBD8()
{
	SET(3, mRegisterB);
}

void CPU::_CBD9()
{
	SET(3, mRegisterC);
}

void CPU::_CBDA()
{
	SET(3, mRegisterD);
}

void CPU::_CBDB()
{
	SET(3, mRegisterE);
}

void CPU::_CBDC()
{
	SET(3, mRegisterH);
}

void CPU::_CBDD()
{
	SET(3, mRegisterL);
}

void CPU::_CBDE()
{
	SET(3, mRegisterHL.RegisterAsAddress());
}

void CPU::_CBDF()
{
	SET(3, mRegisterA);
}


// OPCODES CBEX
void CPU::_CBE0()
{
	SET(4, mRegisterB);
}

void CPU::_CBE1()
{
	SET(4, mRegisterC);
}

void CPU::_CBE2()
{
	SET(4, mRegisterD);
}

void CPU::_CBE3()
{
	SET(4, mRegisterE);
}

void CPU::_CBE4()
{
	SET(4, mRegisterH);
}

void CPU::_CBE5()
{
	SET(4, mRegisterL);
}

void CPU::_CBE6()
{
	SET(4, mRegisterHL.RegisterAsAddress());
}

void CPU::_CBE7()
{
	SET(4, mRegisterA);
}

void CPU::_CBE8()
{
	SET(5, mRegisterB);
}

void CPU::_CBE9()
{
	SET(5, mRegisterC);
}

void CPU::_CBEA()
{
	SET(5, mRegisterD);
}

void CPU::_CBEB()
{
	SET(5, mRegisterE);
}

void CPU::_CBEC()
{
	SET(5, mRegisterH);
}

void CPU::_CBED()
{
	SET(5, mRegisterL);
}

void CPU::_CBEE()
{
	SET(5, mRegisterHL.RegisterAsAddress());
}

void CPU::_CBEF()
{
	SET(5, mRegisterA);
}


// OPCODES CBFX
void CPU::_CBF0()
{
	SET(6, mRegisterB);
}

void CPU::_CBF1()
{
	SET(6, mRegisterC);
}

void CPU::_CBF2()
{
	SET(6, mRegisterD);
}

void CPU::_CBF3()
{
	SET(6, mRegisterE);
}

void CPU::_CBF4()
{
	SET(6, mRegisterH);
}

void CPU::_CBF5()
{
	SET(6, mRegisterL);
}

void CPU::_CBF6()
{
	SET(6, mRegisterHL.RegisterAsAddress());
}

void CPU::_CBF7()
{
	SET(6, mRegisterA);
}

void CPU::_CBF8()
{
	SET(7, mRegisterB);
}

void CPU::_CBF9()
{
	SET(7, mRegisterC);
}

void CPU::_CBFA()
{
	SET(7, mRegisterD);
}

void CPU::_CBFB()
{
	SET(7, mRegisterE);
}

void CPU::_CBFC()
{
	SET(7, mRegisterH);
}

void CPU::_CBFD()
{
	SET(7, mRegisterL);
}

void CPU::_CBFE()
{
	SET(7, mRegisterHL.RegisterAsAddress());
}

void CPU::_CBFF()
{
	SET(7, mRegisterA);
}