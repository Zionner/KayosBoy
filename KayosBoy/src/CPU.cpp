#include "CPU.hpp"
#include <iostream>

CPU::CPU(Memory& mem) :
	mRegisterA(0), // Accumulator Register
	mRegisterB(0),
	mRegisterC(0),
	mRegisterD(0),
	mRegisterE(0),
	mRegisterF(0),
	mRegisterG(0),
	mRegisterH(0),
	mRegisterL(0),
	mRegisterAF(mRegisterA, mRegisterF),
	mRegisterBC(mRegisterB, mRegisterC),
	mRegisterDE(mRegisterD, mRegisterE),
	mRegisterHL(mRegisterH, mRegisterL),
	mMemory(mem)
{
	SetupCommandStructure();
}

void CPU::PushOntoStackPointer(uint16_t val) 
{
	mStackPointer.Decrement();
	mStackPointer.Decrement();
	mMemory.WriteTwoBytesAtPointer(mStackPointer.RegisterAsAddress(), val);
}

void CPU::PushOntoStackPointer(PairedByteRegister& reg)
{
	mStackPointer.Decrement();
	mStackPointer.Decrement();
	mMemory.WriteTwoBytesAtPointer(mStackPointer.RegisterAsAddress(), reg.GetRegisterValue().PairedBytes);
}

void CPU::PushOntoStackPointer(TwoByteRegister& reg)
{
	mStackPointer.Decrement();
	mStackPointer.Decrement();
	mMemory.WriteTwoBytesAtPointer(mStackPointer.RegisterAsAddress(), reg.GetRegisterValue().PairedBytes);
}


void CPU::PopFromStackPointer(PairedByteRegister& reg)
{
	mStackPointer.Increment();
	uint16_t result = mMemory.ReadTwoBytesAtPointer(mStackPointer.RegisterAsAddress());
	mStackPointer.Increment();

	reg.SetRegister(result);
}

void CPU::PopFromStackPointer(TwoByteRegister& reg)
{
	mStackPointer.Increment();
	uint16_t result = mMemory.ReadTwoBytesAtPointer(mStackPointer.RegisterAsAddress());
	mStackPointer.Increment();

	reg.SetRegister(result);
}

bool CPU::IsCPUInCondition(Condition condition)
{
	switch (condition)
	{
	case Carry:
		return mRegisterF.GetCarryFlag();
	case NotCarry:
		return !mRegisterF.GetCarryFlag();
	case Zero:
		return mRegisterF.GetZeroFlag();
	case NotZero:
		return !mRegisterF.GetZeroFlag();
	default:
		return false;
	}
}

uint8_t CPU::ReadByteFromProgramCounter()
{
	uint8_t byte = mMemory.ReadByteAtPointer(mProgramCounter.RegisterAsAddress());
	mProgramCounter.Increment();

	return byte;
}

uint16_t CPU::ReadTwoBytesFromProgramCounter()
{
	uint16_t bytes = mMemory.ReadTwoBytesAtPointer(mProgramCounter.RegisterAsAddress());
	mProgramCounter.Increment();
	mProgramCounter.Increment();

	return bytes;
}

KayosBoyPtr CPU::ReadAddressFromProgramCounter()
{
	KayosBoyPtr addr(mMemory.ReadTwoBytesAtPointer(mProgramCounter.RegisterAsAddress()));
	mProgramCounter.Increment();
	mProgramCounter.Increment();

	return addr;
}

uint64_t CPU::Tick()
{
	mTickElapsedCycles = 0;

	uint8_t opcode = ReadByteFromProgramCounter();
 	(this->*mOpCodeCommands[opcode])();

	return mTickElapsedCycles;
}

// ADC
void CPU::ADC()
{
	ADC(ReadByteFromProgramCounter());
	mTickElapsedCycles += 2;
}

void CPU::ADC(uint8_t val)
{
	uint8_t aVal = mRegisterA.GetRegisterValue().ByteMemory;
	uint8_t carryVal = static_cast<uint8_t>(mRegisterF.GetCarryFlag() ? 1 : 0);
	uint8_t result = aVal + val + carryVal;

	mRegisterA.SetRegister(result);

	mRegisterF.SetZeroFlag(result == 0);
	mRegisterF.SetSubtractFlag(false);
	mRegisterF.SetHalfCarryFlag(((aVal & 0xF) + (val & 0xF) + carryVal) > 0xF);
	mRegisterF.SetCarryFlag(result > 0xFF);
}

void CPU::ADC(ByteRegister& val)
{
	ADC(val.GetRegisterValue().ByteMemory);
	mTickElapsedCycles += 1;
}

void CPU::ADC(KayosBoyPtr& ptrToVal)
{
	ADC(mMemory.ReadByteAtPointer(ptrToVal));
	mTickElapsedCycles += 2;
}

// ADD
void CPU::ADD()
{
	ADD(ReadByteFromProgramCounter());
	mTickElapsedCycles += 2;
}

void CPU::ADD_SP()
{
	uint16_t aVal = mStackPointer.GetRegisterValue().PairedBytes;
	int8_t val = static_cast<int8_t>(ReadByteFromProgramCounter());
	int16_t result = aVal + val;

	mStackPointer.SetRegister(static_cast<uint8_t>(result));

	mRegisterF.SetZeroFlag(false);
	mRegisterF.SetSubtractFlag(false);
	mRegisterF.SetHalfCarryFlag(((aVal ^ val ^ (result & 0xFFFF)) & 0x10) == 0x10);
	mRegisterF.SetCarryFlag(((aVal ^ val ^ (result & 0xFFFF)) & 0x100) == 0x100);

	mTickElapsedCycles += 4;
}

void CPU::ADD(uint8_t val)
{
	uint8_t aVal = mRegisterA.GetRegisterValue().ByteMemory;
	uint8_t result = aVal + val;

	mRegisterA.SetRegister(result);

	mRegisterF.SetZeroFlag(result == 0);
	mRegisterF.SetSubtractFlag(false);
	mRegisterF.SetHalfCarryFlag(((aVal & 0xF) + (val & 0xF)) > 0xF);
	mRegisterF.SetCarryFlag((result & 0x100) != 0);
}

void CPU::ADD(uint16_t val)
{
	uint16_t aVal = mRegisterHL.GetRegisterValue().PairedBytes;
	uint16_t result = aVal + val;

	mRegisterHL.SetRegister(result);

	mRegisterF.SetSubtractFlag(false);
	mRegisterF.SetHalfCarryFlag(((aVal & 0xFFF) + (val & 0xFFF)) > 0xFFF);
	mRegisterF.SetCarryFlag((result & 0x10000) != 0);
}

void CPU::ADD(ByteRegister& val)
{
	ADD(val.GetRegisterValue().ByteMemory);
	mTickElapsedCycles += 1;
}

void CPU::ADD(TwoByteRegister& val)
{
	ADD(val.GetRegisterValue().PairedBytes);
	mTickElapsedCycles += 2;
}

void CPU::ADD(PairedByteRegister& val)
{
	ADD(val.GetRegisterValue().PairedBytes);
	mTickElapsedCycles += 2;
}

void CPU::ADD(KayosBoyPtr& ptrToVal)
{
	ADD(mMemory.ReadByteAtPointer(ptrToVal));
	mTickElapsedCycles += 2;
}

// AND
void CPU::AND()
{
	AND(ReadByteFromProgramCounter());
	mTickElapsedCycles += 2;
}

void CPU::AND(uint8_t val)
{
	uint8_t reg = mRegisterA.GetRegisterValue().ByteMemory;
	uint8_t result = reg & val;

	mRegisterA.SetRegister(result);

	mRegisterF.SetZeroFlag(result == 0);
	mRegisterF.SetSubtractFlag(true);
	mRegisterF.SetHalfCarryFlag(false);
	mRegisterF.SetCarryFlag(false);
}

void CPU::AND(ByteRegister& val)
{
	AND(val.GetRegisterValue().ByteMemory);
	mTickElapsedCycles += 1;
}

void CPU::AND(KayosBoyPtr& ptrToVal)
{
	AND(mMemory.ReadByteAtPointer(ptrToVal));
	mTickElapsedCycles += 2;
}

// BIT
void CPU::BIT(uint8_t bit, ByteRegister& registerToTest)
{
	mRegisterF.SetZeroFlag(registerToTest.GetRegisterBit(bit) == 0);
	mRegisterF.SetSubtractFlag(false);
	mRegisterF.SetHalfCarryFlag(true);
	mTickElapsedCycles += 2;
}

void CPU::BIT(uint8_t bit, KayosBoyPtr& addressToByteToTest)
{
	mRegisterF.SetZeroFlag((mMemory.ReadByteAtPointer(addressToByteToTest) & (1 << bit)) == 0);
	mRegisterF.SetSubtractFlag(false);
	mRegisterF.SetHalfCarryFlag(true);
	mTickElapsedCycles += 3;
}

// CALL
void CPU::CALL()
{
	uint16_t addr = ReadTwoBytesFromProgramCounter();
	PushOntoStackPointer(addr);
	mProgramCounter.SetRegister(addr);
	mTickElapsedCycles += 24;
}

void CPU::CALL(Condition flagCondition)
{
	if (IsCPUInCondition(flagCondition))
	{
		CALL();
	}
	else
	{
		ReadTwoBytesFromProgramCounter();
		mTickElapsedCycles += 12;
	}
}

// CCF
void CPU::CCF()
{
	mRegisterF.SetSubtractFlag(false);
	mRegisterF.SetHalfCarryFlag(false);
	mRegisterF.SetCarryFlag(!mRegisterF.GetCarryFlag());
	mTickElapsedCycles += 1;
}

// CP
void CPU::CP()
{
	CP(ReadByteFromProgramCounter());
	mTickElapsedCycles += 1;
}

void CPU::CP(uint8_t val)
{
	uint8_t aVal = mRegisterA.GetRegisterValue().ByteMemory;
	uint8_t result = aVal - val;

	mRegisterA.SetRegister(result);

	mRegisterF.SetZeroFlag(result == 0);
	mRegisterF.SetSubtractFlag(true);
	mRegisterF.SetHalfCarryFlag(((aVal & 0xF) - (result & 0xF)) < 0);
	mRegisterF.SetCarryFlag(aVal < result);
	mTickElapsedCycles += 1;
}

void CPU::CP(ByteRegister& val)
{
	CP(val.GetRegisterValue().ByteMemory);
}

void CPU::CP(KayosBoyPtr& ptrToVal)
{
	CP(mMemory.ReadByteAtPointer(ptrToVal));
	mTickElapsedCycles += 1;
}

// CPL
void CPU::CPL()
{
	mRegisterA.SetRegister(~mRegisterA.GetRegisterValue().ByteMemory);
	mTickElapsedCycles += 1;
}

// DAA
void CPU::DAA()
{
	printf("DAA Unimplemented \n");
	mTickElapsedCycles += 1;
}

// DEC
void CPU::DEC(ByteRegister& val)
{
	val.DecrementRegister();

	mRegisterF.SetZeroFlag(val.GetRegisterValue().ByteMemory == 0);
	mRegisterF.SetSubtractFlag(true);
	mRegisterF.SetHalfCarryFlag((val.GetRegisterValue().ByteMemory & 0x0F) == 0x0F);
	mTickElapsedCycles += 1;
}

void CPU::DEC(TwoByteRegister& val)
{
	val.Decrement();
	mTickElapsedCycles += 2;
}

void CPU::DEC(PairedByteRegister& val)
{
	val.Decrement();
	mTickElapsedCycles += 2;
}

void CPU::DEC(KayosBoyPtr& ptrToVal)
{
	uint8_t val = mMemory.ReadByteAtPointer(ptrToVal);
	val++;
	mMemory.WriteByteAtPointer(ptrToVal, val);

	mRegisterF.SetZeroFlag(val == 0);
	mRegisterF.SetSubtractFlag(true);
	mRegisterF.SetHalfCarryFlag((val & 0x0F) == 0x0F);
	mTickElapsedCycles += 3;
}

// DI
void CPU::DI()
{
	mIsInterruptsEnabled = false;
	mTickElapsedCycles += 1;
}

// EI
void CPU::EI()
{
	mIsInterruptsEnabled = true;
	mTickElapsedCycles += 1;
}

// HALT
void CPU::HALT()
{
	printf("HALT Unimplemented \n");
	mTickElapsedCycles += 1;
	// TODO
}

// INC
void CPU::INC(ByteRegister& val)
{
	val.IncrementRegister();

	mRegisterF.SetZeroFlag(val.GetRegisterValue().ByteMemory == 0);
	mRegisterF.SetSubtractFlag(true);
	mRegisterF.SetHalfCarryFlag((val.GetRegisterValue().ByteMemory & 0x0F) == 0x0F);
	mTickElapsedCycles += 1;
}

void CPU::INC(TwoByteRegister& val)
{
	val.Increment();
	mTickElapsedCycles += 2;
}

void CPU::INC(PairedByteRegister& val)
{
	val.Increment();
	mTickElapsedCycles += 2;
}

void CPU::INC(KayosBoyPtr& ptrToVal)
{
	uint8_t val = mMemory.ReadByteAtPointer(ptrToVal);
	val--;
	mMemory.WriteByteAtPointer(ptrToVal, val);

	mRegisterF.SetZeroFlag(val == 0);
	mRegisterF.SetSubtractFlag(true);
	mRegisterF.SetHalfCarryFlag((val & 0x0F) == 0x0F);
	mTickElapsedCycles += 3;
}

// JP
void CPU::JP()
{
	uint16_t addr = ReadTwoBytesFromProgramCounter();
	mProgramCounter.SetRegister(addr);
	mTickElapsedCycles += 4;
}

void CPU::JP(Condition flagCondition)
{
	if (IsCPUInCondition(flagCondition))
	{
		JP();
	}
	else
	{
		ReadTwoBytesFromProgramCounter();
		mTickElapsedCycles += 3;
	}
}

void CPU::JP(KayosBoyPtr& ptr)
{
	mProgramCounter.SetRegister(ptr.GetPointerVal());
	mTickElapsedCycles += 1;
}

// JR
void CPU::JR()
{
	int8_t offset = static_cast<int8_t>(ReadByteFromProgramCounter());
	uint16_t result = mProgramCounter.GetRegisterValue().PairedBytes + offset;

	mProgramCounter.SetRegister(result);
	mTickElapsedCycles += 3;
}

void CPU::JR(Condition flagCondition)
{
	if (IsCPUInCondition(flagCondition))
	{
		JR();
	}
	else
	{
		ReadByteFromProgramCounter();
		mTickElapsedCycles += 2;
	}
}

// LD
void CPU::LD_PC(ByteRegister& registerToSet)
{
	registerToSet.SetRegister(ReadByteFromProgramCounter());
	mTickElapsedCycles += 2;
}

void CPU::LD_PC(KayosBoyPtr& ptrToSet)
{
	mMemory.WriteByteAtPointer(ptrToSet, ReadByteFromProgramCounter());
	mTickElapsedCycles += 2;
}

void CPU::LD_PC(PairedByteRegister& val)
{
	val.SetRegister(ReadTwoBytesFromProgramCounter());
	mTickElapsedCycles += 2;
}

void CPU::LD_PC(TwoByteRegister& registerToSet)
{
	registerToSet.SetRegister(ReadTwoBytesFromProgramCounter());
	mTickElapsedCycles += 2;
}

void CPU::LD_PCAddress(ByteRegister& registerToSet)
{
	registerToSet.SetRegister(mMemory.ReadByteAtPointer(ReadAddressFromProgramCounter()));
	mTickElapsedCycles += 3;
}

void CPU::LD_WriteToPCAddress(ByteRegister& registerToSet)
{
	mMemory.WriteByteAtPointer(ReadAddressFromProgramCounter(), registerToSet.GetRegisterValue().ByteMemory);
	mTickElapsedCycles += 3;
}

void CPU::LD_WriteToPCAddress(TwoByteRegister& registerToSet)
{
	mMemory.WriteTwoBytesAtPointer(ReadAddressFromProgramCounter(), registerToSet.GetRegisterValue().PairedBytes);
	mTickElapsedCycles += 3;
}

void CPU::LD(ByteRegister& registerToSet, ByteRegister& val)
{
	registerToSet.SetRegister(val.GetRegisterValue().ByteMemory);
	mTickElapsedCycles += 1;
}

void CPU::LD(ByteRegister& registerToSet, KayosBoyPtr& val)
{
	registerToSet.SetRegister(mMemory.ReadByteAtPointer(val));
	mTickElapsedCycles += 2;
}

void CPU::LD(TwoByteRegister& registerToSet, PairedByteRegister& val)
{
	registerToSet.SetRegister(val.GetRegisterValue().PairedBytes);
	mTickElapsedCycles += 3;
}

void CPU::LD(KayosBoyPtr& ptrToSet, ByteRegister& val)
{
	mMemory.WriteByteAtPointer(ptrToSet, val.GetRegisterValue().ByteMemory);
	mTickElapsedCycles += 2;
}

void CPU::LD(KayosBoyPtr& ptrToSet, TwoByteRegister& val)
{
	mMemory.WriteTwoBytesAtPointer(ptrToSet, val.GetRegisterValue().PairedBytes);
	mTickElapsedCycles += 5;
}

// LDD
void CPU::LDD(ByteRegister& registerToSet, KayosBoyPtr& val)
{
	registerToSet.SetRegister(mMemory.ReadByteAtPointer(val));
	mRegisterHL.Decrement();
	mTickElapsedCycles += 2;
}

void CPU::LDD(KayosBoyPtr& ptrToSet, ByteRegister& val)
{
	mMemory.WriteByteAtPointer(ptrToSet, val.GetRegisterValue().ByteMemory);
	mRegisterHL.Decrement();
	mTickElapsedCycles += 2;
}

// LDH
void CPU::LDH_A()
{
	int8_t val = static_cast<int8_t>(ReadByteFromProgramCounter());
	mRegisterA.SetRegister(mMemory.ReadByteAtPointer(KayosBoyPtr(0xFF00 + val)));
	mTickElapsedCycles += 3;
}

void CPU::LDH_PC()
{
	int8_t val = static_cast<int8_t>(ReadByteFromProgramCounter());
	mMemory.WriteByteAtPointer(mMemory.ReadByteAtPointer(KayosBoyPtr(0xFF00 + val)), mRegisterA.GetRegisterValue().ByteMemory);
	mTickElapsedCycles += 3;
}

void CPU::LDH_C()
{
	mMemory.WriteByteAtPointer(KayosBoyPtr(0xFF00 + mRegisterC.GetRegisterValue().ByteMemory), mRegisterA.GetRegisterValue().ByteMemory);
	mTickElapsedCycles += 2;
}

void CPU::LDH_CAddr_A()
{
	mRegisterA.SetRegister(mMemory.ReadByteAtPointer(KayosBoyPtr(0xFF00 + mRegisterC.GetRegisterValue().ByteMemory)));
	mTickElapsedCycles += 2;
}

// LDHL
void CPU::LDHL()
{
	int8_t offset = static_cast<int8_t>(ReadByteFromProgramCounter());
	uint16_t result = mStackPointer.GetRegisterValue().PairedBytes + offset;

	mRegisterHL.SetRegister(result);

	mRegisterF.SetZeroFlag(false);
	mRegisterF.SetSubtractFlag(false);
	mRegisterF.SetHalfCarryFlag(((mStackPointer.GetRegisterValue().PairedBytes ^ offset ^ (result & 0xFFFF)) & 0x10) == 0x10);
	mRegisterF.SetCarryFlag(((mStackPointer.GetRegisterValue().PairedBytes ^ offset ^ (result & 0xFFFF)) & 0x100) == 0x100);
	mTickElapsedCycles += 3;
}

// LDI
void CPU::LDI(ByteRegister& registerToSet, KayosBoyPtr& val)
{
	registerToSet.SetRegister(mMemory.ReadByteAtPointer(val));
	mRegisterHL.Increment();
	mTickElapsedCycles += 2;
}

void CPU::LDI(KayosBoyPtr& addressToSet, ByteRegister& val)
{
	mMemory.WriteByteAtPointer(addressToSet, val.GetRegisterValue().ByteMemory);
	mRegisterHL.Increment();
	mTickElapsedCycles += 2;
}

// NOP
void CPU::NOP()
{
	// Blank..?
	mTickElapsedCycles += 1;
}

// OR
void CPU::OR()
{
	OR(ReadByteFromProgramCounter());
	mTickElapsedCycles += 2;
}

void CPU::OR(uint8_t val)
{
	uint8_t aVal = mRegisterA.GetRegisterValue().ByteMemory;
	uint8_t result = aVal | val;

	mRegisterA.SetRegister(result);

	mRegisterF.SetZeroFlag(result == 0);
	mRegisterF.SetSubtractFlag(false);
	mRegisterF.SetHalfCarryFlag(false);
	mRegisterF.SetCarryFlag(false);
	
}

void CPU::OR(ByteRegister& val)
{
	OR(val.GetRegisterValue().ByteMemory);
	mTickElapsedCycles += 1;
}

void CPU::OR(KayosBoyPtr& ptrToVal)
{
	OR(mMemory.ReadByteAtPointer(ptrToVal));
	mTickElapsedCycles += 2;
}

// POP
void CPU::POP(PairedByteRegister& val)
{
	PopFromStackPointer(val);
	mTickElapsedCycles += 3;
}

// PUSH
void CPU::PUSH(PairedByteRegister& val)
{
	PushOntoStackPointer(val);
	mTickElapsedCycles += 4;
}

// RES
void CPU::RES(uint8_t bit, ByteRegister& registerToReset)
{
	registerToReset.SetRegisterBit(bit, false);
	mTickElapsedCycles += 2;
}

void CPU::RES(uint8_t bit, KayosBoyPtr& addressToByteToReset)
{
	uint8_t value = mMemory.ReadByteAtPointer(addressToByteToReset);
	value |= 0 << bit;
	mMemory.WriteByteAtPointer(addressToByteToReset, value);
	mTickElapsedCycles += 4;
}

// RET
void CPU::RET()
{
	PopFromStackPointer(mProgramCounter);
}

void CPU::RET(Condition flagCondition)
{
	if (IsCPUInCondition(flagCondition))
	{
		RET();
		mTickElapsedCycles += 5;
	}
	else
	{
		mTickElapsedCycles += 2;
	}
}

// RETI
void CPU::RETI()
{
	RET();
	EI();
	mTickElapsedCycles += 4;
}

// RLA
void CPU::RLA()
{
	printf("RLA not implemented \n");
	mTickElapsedCycles += 1;
}

// RLCA
void CPU::RLCA()
{
	printf("RLCA not implemented \n");
	mTickElapsedCycles += 1;
}

// RLC
void CPU::RLC(ByteRegister& registerToRotate)
{
	printf("RLC not implemented \n");
	mTickElapsedCycles += 2;
}

void CPU::RLC(KayosBoyPtr& addressToByteToRotate)
{
	printf("RLC not implemented \n");
	mTickElapsedCycles += 4;
}

// RL
void CPU::RL(ByteRegister& registerToRotate)
{
	printf("RL not implemented \n");
	mTickElapsedCycles += 2;
}

void CPU::RL(KayosBoyPtr& addressToByteToRotate)
{
	printf("RL not implemented \n");
	mTickElapsedCycles += 4;
}

// RRA
void CPU::RRA()
{
	printf("RRA not implemented \n");
	mTickElapsedCycles += 1;
}

// RRCA
void CPU::RRCA()
{
	printf("RRCA not implemented \n");
	mTickElapsedCycles += 1;
}

// RRC
void CPU::RRC(ByteRegister& registerToRotate)
{
	printf("RRC not implemented \n");
	mTickElapsedCycles += 2;
}

void CPU::RRC(KayosBoyPtr& addressToByteToRotate)
{
	printf("RRC not implemented \n");
	mTickElapsedCycles += 4;
}

// RR
void CPU::RR(ByteRegister& registerToRotate)
{
	printf("RR not implemented \n");
	mTickElapsedCycles += 2;
}

void CPU::RR(KayosBoyPtr& addressToByteToRotate)
{
	printf("RR not implemented \n");
	mTickElapsedCycles += 4;
}

// RST
void CPU::RST(uint8_t offset)
{
	PushOntoStackPointer(mProgramCounter.GetRegisterValue().PairedBytes);
	mProgramCounter.SetRegister(offset);
	mTickElapsedCycles += 4;
}

// SBC
void CPU::SBC()
{
	printf("SBC not implemented \n");
	mTickElapsedCycles += 2;
}

void CPU::SBC(uint8_t val)
{
	printf("SBC not implemented \n");
}

void CPU::SBC(ByteRegister& val)
{
	printf("SBC not implemented \n");
	mTickElapsedCycles += 1;
}

void CPU::SBC(KayosBoyPtr& ptrToVal)
{
	printf("SBC not implemented \n");
	mTickElapsedCycles += 2;
}

// SCF
void CPU::SCF()
{
	printf("SCF not implemented \n");
	mTickElapsedCycles += 1;
}

// SET
void CPU::SET(uint8_t bit, ByteRegister& registerToSet)
{
	registerToSet.SetRegisterBit(bit, true);
	mTickElapsedCycles += 2;
}

void CPU::SET(uint8_t bit, KayosBoyPtr& addressToByteToSet)
{
	uint8_t value = mMemory.ReadByteAtPointer(addressToByteToSet);
	value |= (1 << bit);
	mMemory.WriteByteAtPointer(addressToByteToSet, value);
	mTickElapsedCycles += 4;
}

// SLA
void CPU::SLA(ByteRegister& registerToShift)
{
	printf("SLA not implemented \n");
	mTickElapsedCycles += 2;
}

void CPU::SLA(KayosBoyPtr& addressToByteToShift)
{
	printf("SLA not implemented \n");
	mTickElapsedCycles += 4;
}

// SRA
void CPU::SRA(ByteRegister& registerToShift)
{
	printf("SRA not implemented \n");
	mTickElapsedCycles += 2;
}

void CPU::SRA(KayosBoyPtr& addressToByteToShift)
{
	printf("SRA not implemented \n");
	mTickElapsedCycles += 4;
}

// SRL
void CPU::SRL(ByteRegister& registerToShift)
{
	printf("SRL not implemented \n");
	mTickElapsedCycles += 2;
}

void CPU::SRL(KayosBoyPtr& addressToByteToShift)
{
	printf("SRL not implemented \n");
	mTickElapsedCycles += 4;
}

// SWAP
void CPU::SWAP(ByteRegister& registerToSwap)
{
	printf("SWAP not implemented \n");
	mTickElapsedCycles += 2;
}

void CPU::SWAP(KayosBoyPtr& addressToByteToSwap)
{
	printf("SWAP not implemented \n");
	mTickElapsedCycles += 4;
}

// STOP
void CPU::STOP()
{
	// Emptry
	mTickElapsedCycles += 1;
}

// SUB
void CPU::SUB()
{
	SUB(ReadByteFromProgramCounter());
	mTickElapsedCycles += 2;
}

void CPU::SUB(uint8_t val)
{
	uint8_t aVal = mRegisterA.GetRegisterValue().ByteMemory;
	uint8_t result = aVal - val;

	mRegisterA.SetRegister(result);

	mRegisterF.SetZeroFlag(result == 0);
	mRegisterF.SetSubtractFlag(true);
	mRegisterF.SetHalfCarryFlag(((aVal & 0xF) - (val & 0xF)) < 0);
	mRegisterF.SetCarryFlag(aVal < val);
}

void CPU::SUB(ByteRegister& val)
{
	SUB(val.GetRegisterValue().ByteMemory);
	mTickElapsedCycles += 1;
}

void CPU::SUB(KayosBoyPtr& ptrToVal)
{
	SUB(mMemory.ReadByteAtPointer(ptrToVal));
	mTickElapsedCycles += 2;
}

// XOR
void CPU::XOR()
{
	XOR(ReadByteFromProgramCounter());
	mTickElapsedCycles += 2;
}

void CPU::XOR(uint8_t val)
{
	uint8_t result = mRegisterA.GetRegisterValue().ByteMemory ^ val;

	mRegisterA.SetRegister(result);

	mRegisterF.SetZeroFlag(result == 0);
	mRegisterF.SetSubtractFlag(false);
	mRegisterF.SetHalfCarryFlag(false);
	mRegisterF.SetCarryFlag(false);
}

void CPU::XOR(ByteRegister& val)
{
	XOR(val.GetRegisterValue().ByteMemory);
	mTickElapsedCycles += 1;
}

void CPU::XOR(KayosBoyPtr& ptrToVal)
{
	XOR(mMemory.ReadByteAtPointer(ptrToVal));
	mTickElapsedCycles += 2;
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
	LD_PC(mRegisterHL);
}

void CPU::_22()
{
	LDI(mRegisterHL.RegisterAsAddress(), mRegisterA);
}

void CPU::_23()
{
	INC(mRegisterHL);
}

void CPU::_24()
{
	INC(mRegisterH);
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

void CPU::_BB_()
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

void CPU::_C2_()
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
	uint8_t newOpCode = ReadByteFromProgramCounter();
	(this->*mCBOpCodeCommands[newOpCode])();
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
	LDH_PC();
}

void CPU::_E1()
{
	POP(mRegisterHL);
}

void CPU::_E2()
{
	LDH_CAddr_A();
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
	LD_WriteToPCAddress(mRegisterA);
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
	printf("_FA Unimplemented");
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

void CPU::SetupCommandStructure()
{
	// Opcodes 0x0X
	mOpCodeCommands.push_back(&CPU::_00);
	mOpCodeCommands.push_back(&CPU::_01);
	mOpCodeCommands.push_back(&CPU::_02);
	mOpCodeCommands.push_back(&CPU::_03);
	mOpCodeCommands.push_back(&CPU::_04);
	mOpCodeCommands.push_back(&CPU::_05);
	mOpCodeCommands.push_back(&CPU::_06);
	mOpCodeCommands.push_back(&CPU::_07);
	mOpCodeCommands.push_back(&CPU::_08);
	mOpCodeCommands.push_back(&CPU::_09);
	mOpCodeCommands.push_back(&CPU::_0A);
	mOpCodeCommands.push_back(&CPU::_0B);
	mOpCodeCommands.push_back(&CPU::_0C);
	mOpCodeCommands.push_back(&CPU::_0D);
	mOpCodeCommands.push_back(&CPU::_0E);
	mOpCodeCommands.push_back(&CPU::_0F);

	// Opcodes 0x1X
	mOpCodeCommands.push_back(&CPU::_10);
	mOpCodeCommands.push_back(&CPU::_11);
	mOpCodeCommands.push_back(&CPU::_12);
	mOpCodeCommands.push_back(&CPU::_13);
	mOpCodeCommands.push_back(&CPU::_14);
	mOpCodeCommands.push_back(&CPU::_15);
	mOpCodeCommands.push_back(&CPU::_16);
	mOpCodeCommands.push_back(&CPU::_17);
	mOpCodeCommands.push_back(&CPU::_18);
	mOpCodeCommands.push_back(&CPU::_19);
	mOpCodeCommands.push_back(&CPU::_1A);
	mOpCodeCommands.push_back(&CPU::_1B);
	mOpCodeCommands.push_back(&CPU::_1C);
	mOpCodeCommands.push_back(&CPU::_1D);
	mOpCodeCommands.push_back(&CPU::_1E);
	mOpCodeCommands.push_back(&CPU::_1F);

	// Opcodes 0x2X
	mOpCodeCommands.push_back(&CPU::_20);
	mOpCodeCommands.push_back(&CPU::_21);
	mOpCodeCommands.push_back(&CPU::_22);
	mOpCodeCommands.push_back(&CPU::_23);
	mOpCodeCommands.push_back(&CPU::_24);
	mOpCodeCommands.push_back(&CPU::_25);
	mOpCodeCommands.push_back(&CPU::_26);
	mOpCodeCommands.push_back(&CPU::_27);
	mOpCodeCommands.push_back(&CPU::_28);
	mOpCodeCommands.push_back(&CPU::_29);
	mOpCodeCommands.push_back(&CPU::_2A);
	mOpCodeCommands.push_back(&CPU::_2B);
	mOpCodeCommands.push_back(&CPU::_2C);
	mOpCodeCommands.push_back(&CPU::_2D);
	mOpCodeCommands.push_back(&CPU::_2E);
	mOpCodeCommands.push_back(&CPU::_2F);

	// Opcodes 0x3X
	mOpCodeCommands.push_back(&CPU::_30);
	mOpCodeCommands.push_back(&CPU::_31);
	mOpCodeCommands.push_back(&CPU::_32);
	mOpCodeCommands.push_back(&CPU::_33);
	mOpCodeCommands.push_back(&CPU::_34);
	mOpCodeCommands.push_back(&CPU::_35);
	mOpCodeCommands.push_back(&CPU::_36);
	mOpCodeCommands.push_back(&CPU::_37);
	mOpCodeCommands.push_back(&CPU::_38);
	mOpCodeCommands.push_back(&CPU::_39);
	mOpCodeCommands.push_back(&CPU::_3A);
	mOpCodeCommands.push_back(&CPU::_3B);
	mOpCodeCommands.push_back(&CPU::_3C);
	mOpCodeCommands.push_back(&CPU::_3D);
	mOpCodeCommands.push_back(&CPU::_3E);
	mOpCodeCommands.push_back(&CPU::_3F);

	// Opcodes 0x4X
	mOpCodeCommands.push_back(&CPU::_40);
	mOpCodeCommands.push_back(&CPU::_41);
	mOpCodeCommands.push_back(&CPU::_42);
	mOpCodeCommands.push_back(&CPU::_43);
	mOpCodeCommands.push_back(&CPU::_44);
	mOpCodeCommands.push_back(&CPU::_45);
	mOpCodeCommands.push_back(&CPU::_46);
	mOpCodeCommands.push_back(&CPU::_47);
	mOpCodeCommands.push_back(&CPU::_48);
	mOpCodeCommands.push_back(&CPU::_49);
	mOpCodeCommands.push_back(&CPU::_4A);
	mOpCodeCommands.push_back(&CPU::_4B);
	mOpCodeCommands.push_back(&CPU::_4C);
	mOpCodeCommands.push_back(&CPU::_4D);
	mOpCodeCommands.push_back(&CPU::_4E);
	mOpCodeCommands.push_back(&CPU::_4F);

	// Opcodes 0x5X
	mOpCodeCommands.push_back(&CPU::_50);
	mOpCodeCommands.push_back(&CPU::_51);
	mOpCodeCommands.push_back(&CPU::_52);
	mOpCodeCommands.push_back(&CPU::_53);
	mOpCodeCommands.push_back(&CPU::_54);
	mOpCodeCommands.push_back(&CPU::_55);
	mOpCodeCommands.push_back(&CPU::_56);
	mOpCodeCommands.push_back(&CPU::_57);
	mOpCodeCommands.push_back(&CPU::_58);
	mOpCodeCommands.push_back(&CPU::_59);
	mOpCodeCommands.push_back(&CPU::_5A);
	mOpCodeCommands.push_back(&CPU::_5B);
	mOpCodeCommands.push_back(&CPU::_5C);
	mOpCodeCommands.push_back(&CPU::_5D);
	mOpCodeCommands.push_back(&CPU::_5E);
	mOpCodeCommands.push_back(&CPU::_5F);

	// Opcodes 0x6X
	mOpCodeCommands.push_back(&CPU::_60);
	mOpCodeCommands.push_back(&CPU::_61);
	mOpCodeCommands.push_back(&CPU::_62);
	mOpCodeCommands.push_back(&CPU::_63);
	mOpCodeCommands.push_back(&CPU::_64);
	mOpCodeCommands.push_back(&CPU::_65);
	mOpCodeCommands.push_back(&CPU::_66);
	mOpCodeCommands.push_back(&CPU::_67);
	mOpCodeCommands.push_back(&CPU::_68);
	mOpCodeCommands.push_back(&CPU::_69);
	mOpCodeCommands.push_back(&CPU::_6A);
	mOpCodeCommands.push_back(&CPU::_6B);
	mOpCodeCommands.push_back(&CPU::_6C);
	mOpCodeCommands.push_back(&CPU::_6D);
	mOpCodeCommands.push_back(&CPU::_6E);
	mOpCodeCommands.push_back(&CPU::_6F);

	// Opcodes 0x7X
	mOpCodeCommands.push_back(&CPU::_70);
	mOpCodeCommands.push_back(&CPU::_71);
	mOpCodeCommands.push_back(&CPU::_72);
	mOpCodeCommands.push_back(&CPU::_73);
	mOpCodeCommands.push_back(&CPU::_74);
	mOpCodeCommands.push_back(&CPU::_75);
	mOpCodeCommands.push_back(&CPU::_76);
	mOpCodeCommands.push_back(&CPU::_77);
	mOpCodeCommands.push_back(&CPU::_78);
	mOpCodeCommands.push_back(&CPU::_79);
	mOpCodeCommands.push_back(&CPU::_7A);
	mOpCodeCommands.push_back(&CPU::_7B);
	mOpCodeCommands.push_back(&CPU::_7C);
	mOpCodeCommands.push_back(&CPU::_7D);
	mOpCodeCommands.push_back(&CPU::_7E);
	mOpCodeCommands.push_back(&CPU::_7F);

	// Opcodes 0x8X
	mOpCodeCommands.push_back(&CPU::_80);
	mOpCodeCommands.push_back(&CPU::_81);
	mOpCodeCommands.push_back(&CPU::_82);
	mOpCodeCommands.push_back(&CPU::_83);
	mOpCodeCommands.push_back(&CPU::_84);
	mOpCodeCommands.push_back(&CPU::_85);
	mOpCodeCommands.push_back(&CPU::_86);
	mOpCodeCommands.push_back(&CPU::_87);
	mOpCodeCommands.push_back(&CPU::_88);
	mOpCodeCommands.push_back(&CPU::_89);
	mOpCodeCommands.push_back(&CPU::_8A);
	mOpCodeCommands.push_back(&CPU::_8B);
	mOpCodeCommands.push_back(&CPU::_8C);
	mOpCodeCommands.push_back(&CPU::_8D);
	mOpCodeCommands.push_back(&CPU::_8E);
	mOpCodeCommands.push_back(&CPU::_8F);

	// Opcodes 0x9X
	mOpCodeCommands.push_back(&CPU::_90);
	mOpCodeCommands.push_back(&CPU::_91);
	mOpCodeCommands.push_back(&CPU::_92);
	mOpCodeCommands.push_back(&CPU::_93);
	mOpCodeCommands.push_back(&CPU::_94);
	mOpCodeCommands.push_back(&CPU::_95);
	mOpCodeCommands.push_back(&CPU::_96);
	mOpCodeCommands.push_back(&CPU::_97);
	mOpCodeCommands.push_back(&CPU::_98);
	mOpCodeCommands.push_back(&CPU::_99);
	mOpCodeCommands.push_back(&CPU::_9A);
	mOpCodeCommands.push_back(&CPU::_9B);
	mOpCodeCommands.push_back(&CPU::_9C);
	mOpCodeCommands.push_back(&CPU::_9D);
	mOpCodeCommands.push_back(&CPU::_9E);
	mOpCodeCommands.push_back(&CPU::_9F);

	// Opcodes 0xAX
	mOpCodeCommands.push_back(&CPU::_A0);
	mOpCodeCommands.push_back(&CPU::_A1);
	mOpCodeCommands.push_back(&CPU::_A2);
	mOpCodeCommands.push_back(&CPU::_A3);
	mOpCodeCommands.push_back(&CPU::_A4);
	mOpCodeCommands.push_back(&CPU::_A5);
	mOpCodeCommands.push_back(&CPU::_A6);
	mOpCodeCommands.push_back(&CPU::_A7);
	mOpCodeCommands.push_back(&CPU::_A8);
	mOpCodeCommands.push_back(&CPU::_A9);
	mOpCodeCommands.push_back(&CPU::_AA);
	mOpCodeCommands.push_back(&CPU::_AB);
	mOpCodeCommands.push_back(&CPU::_AC);
	mOpCodeCommands.push_back(&CPU::_AD);
	mOpCodeCommands.push_back(&CPU::_AE);
	mOpCodeCommands.push_back(&CPU::_AF);

	// Opcodes 0xBX
	mOpCodeCommands.push_back(&CPU::_B0);
	mOpCodeCommands.push_back(&CPU::_B1);
	mOpCodeCommands.push_back(&CPU::_B2);
	mOpCodeCommands.push_back(&CPU::_B3);
	mOpCodeCommands.push_back(&CPU::_B4);
	mOpCodeCommands.push_back(&CPU::_B5);
	mOpCodeCommands.push_back(&CPU::_B6);
	mOpCodeCommands.push_back(&CPU::_B7);
	mOpCodeCommands.push_back(&CPU::_B8);
	mOpCodeCommands.push_back(&CPU::_B9);
	mOpCodeCommands.push_back(&CPU::_BA);
	mOpCodeCommands.push_back(&CPU::_BB_); // again, don't ask.
	mOpCodeCommands.push_back(&CPU::_BC);
	mOpCodeCommands.push_back(&CPU::_BD);
	mOpCodeCommands.push_back(&CPU::_BE);
	mOpCodeCommands.push_back(&CPU::_BF);

	// Opcodes 0xCX
	mOpCodeCommands.push_back(&CPU::_C0);
	mOpCodeCommands.push_back(&CPU::_C1);
	mOpCodeCommands.push_back(&CPU::_C2_); // stop plz
	mOpCodeCommands.push_back(&CPU::_C3);
	mOpCodeCommands.push_back(&CPU::_C4);
	mOpCodeCommands.push_back(&CPU::_C5);
	mOpCodeCommands.push_back(&CPU::_C6);
	mOpCodeCommands.push_back(&CPU::_C7);
	mOpCodeCommands.push_back(&CPU::_C8);
	mOpCodeCommands.push_back(&CPU::_C9);
	mOpCodeCommands.push_back(&CPU::_CA);
	mOpCodeCommands.push_back(&CPU::_CB);
	mOpCodeCommands.push_back(&CPU::_CC);
	mOpCodeCommands.push_back(&CPU::_CD);
	mOpCodeCommands.push_back(&CPU::_CE);
	mOpCodeCommands.push_back(&CPU::_CF);

	// Opcodes 0xDX
	mOpCodeCommands.push_back(&CPU::_D0);
	mOpCodeCommands.push_back(&CPU::_D1);
	mOpCodeCommands.push_back(&CPU::_D2);
	mOpCodeCommands.push_back(&CPU::_D3);
	mOpCodeCommands.push_back(&CPU::_D4);
	mOpCodeCommands.push_back(&CPU::_D5);
	mOpCodeCommands.push_back(&CPU::_D6);
	mOpCodeCommands.push_back(&CPU::_D7);
	mOpCodeCommands.push_back(&CPU::_D8);
	mOpCodeCommands.push_back(&CPU::_D9);
	mOpCodeCommands.push_back(&CPU::_DA);
	mOpCodeCommands.push_back(&CPU::_DB);
	mOpCodeCommands.push_back(&CPU::_DC);
	mOpCodeCommands.push_back(&CPU::_DD);
	mOpCodeCommands.push_back(&CPU::_DE);
	mOpCodeCommands.push_back(&CPU::_DF);

	// Opcodes 0xEX
	mOpCodeCommands.push_back(&CPU::_E0);
	mOpCodeCommands.push_back(&CPU::_E1);
	mOpCodeCommands.push_back(&CPU::_E2);
	mOpCodeCommands.push_back(&CPU::_E3);
	mOpCodeCommands.push_back(&CPU::_E4);
	mOpCodeCommands.push_back(&CPU::_E5);
	mOpCodeCommands.push_back(&CPU::_E6);
	mOpCodeCommands.push_back(&CPU::_E7);
	mOpCodeCommands.push_back(&CPU::_E8);
	mOpCodeCommands.push_back(&CPU::_E9);
	mOpCodeCommands.push_back(&CPU::_EA);
	mOpCodeCommands.push_back(&CPU::_EB);
	mOpCodeCommands.push_back(&CPU::_EC);
	mOpCodeCommands.push_back(&CPU::_ED);
	mOpCodeCommands.push_back(&CPU::_EE);
	mOpCodeCommands.push_back(&CPU::_EF);

	// Opcodes 0x0X
	mOpCodeCommands.push_back(&CPU::_F0);
	mOpCodeCommands.push_back(&CPU::_F1);
	mOpCodeCommands.push_back(&CPU::_F2);
	mOpCodeCommands.push_back(&CPU::_F3);
	mOpCodeCommands.push_back(&CPU::_F4);
	mOpCodeCommands.push_back(&CPU::_F5);
	mOpCodeCommands.push_back(&CPU::_F6);
	mOpCodeCommands.push_back(&CPU::_F7);
	mOpCodeCommands.push_back(&CPU::_F8);
	mOpCodeCommands.push_back(&CPU::_F9);
	mOpCodeCommands.push_back(&CPU::_FA);
	mOpCodeCommands.push_back(&CPU::_FB);
	mOpCodeCommands.push_back(&CPU::_FC);
	mOpCodeCommands.push_back(&CPU::_FD);
	mOpCodeCommands.push_back(&CPU::_FE);
	mOpCodeCommands.push_back(&CPU::_FF);

	// Opcodes 0xCB0X
	mCBOpCodeCommands.push_back(&CPU::_CB00);
	mCBOpCodeCommands.push_back(&CPU::_CB01);
	mCBOpCodeCommands.push_back(&CPU::_CB02);
	mCBOpCodeCommands.push_back(&CPU::_CB03);
	mCBOpCodeCommands.push_back(&CPU::_CB04);
	mCBOpCodeCommands.push_back(&CPU::_CB05);
	mCBOpCodeCommands.push_back(&CPU::_CB06);
	mCBOpCodeCommands.push_back(&CPU::_CB07);
	mCBOpCodeCommands.push_back(&CPU::_CB08);
	mCBOpCodeCommands.push_back(&CPU::_CB09);
	mCBOpCodeCommands.push_back(&CPU::_CB0A);
	mCBOpCodeCommands.push_back(&CPU::_CB0B);
	mCBOpCodeCommands.push_back(&CPU::_CB0C);
	mCBOpCodeCommands.push_back(&CPU::_CB0D);
	mCBOpCodeCommands.push_back(&CPU::_CB0E);
	mCBOpCodeCommands.push_back(&CPU::_CB0F);

	// Opcodes 0xCB01X
	mCBOpCodeCommands.push_back(&CPU::_CB10);
	mCBOpCodeCommands.push_back(&CPU::_CB11);
	mCBOpCodeCommands.push_back(&CPU::_CB12);
	mCBOpCodeCommands.push_back(&CPU::_CB13);
	mCBOpCodeCommands.push_back(&CPU::_CB14);
	mCBOpCodeCommands.push_back(&CPU::_CB15);
	mCBOpCodeCommands.push_back(&CPU::_CB16);
	mCBOpCodeCommands.push_back(&CPU::_CB17);
	mCBOpCodeCommands.push_back(&CPU::_CB18);
	mCBOpCodeCommands.push_back(&CPU::_CB19);
	mCBOpCodeCommands.push_back(&CPU::_CB1A);
	mCBOpCodeCommands.push_back(&CPU::_CB1B);
	mCBOpCodeCommands.push_back(&CPU::_CB1C);
	mCBOpCodeCommands.push_back(&CPU::_CB1D);
	mCBOpCodeCommands.push_back(&CPU::_CB1E);
	mCBOpCodeCommands.push_back(&CPU::_CB1F);

	// Opcodes 0xCB2X
	mCBOpCodeCommands.push_back(&CPU::_CB20);
	mCBOpCodeCommands.push_back(&CPU::_CB21);
	mCBOpCodeCommands.push_back(&CPU::_CB22);
	mCBOpCodeCommands.push_back(&CPU::_CB23);
	mCBOpCodeCommands.push_back(&CPU::_CB24);
	mCBOpCodeCommands.push_back(&CPU::_CB25);
	mCBOpCodeCommands.push_back(&CPU::_CB26);
	mCBOpCodeCommands.push_back(&CPU::_CB27);
	mCBOpCodeCommands.push_back(&CPU::_CB28);
	mCBOpCodeCommands.push_back(&CPU::_CB29);
	mCBOpCodeCommands.push_back(&CPU::_CB2A);
	mCBOpCodeCommands.push_back(&CPU::_CB2B);
	mCBOpCodeCommands.push_back(&CPU::_CB2C);
	mCBOpCodeCommands.push_back(&CPU::_CB2D);
	mCBOpCodeCommands.push_back(&CPU::_CB2E);
	mCBOpCodeCommands.push_back(&CPU::_CB2F);

	// Opcodes 0xCB3X
	mCBOpCodeCommands.push_back(&CPU::_CB30);
	mCBOpCodeCommands.push_back(&CPU::_CB31);
	mCBOpCodeCommands.push_back(&CPU::_CB32);
	mCBOpCodeCommands.push_back(&CPU::_CB33);
	mCBOpCodeCommands.push_back(&CPU::_CB34);
	mCBOpCodeCommands.push_back(&CPU::_CB35);
	mCBOpCodeCommands.push_back(&CPU::_CB36);
	mCBOpCodeCommands.push_back(&CPU::_CB37);
	mCBOpCodeCommands.push_back(&CPU::_CB38);
	mCBOpCodeCommands.push_back(&CPU::_CB39);
	mCBOpCodeCommands.push_back(&CPU::_CB3A);
	mCBOpCodeCommands.push_back(&CPU::_CB3B);
	mCBOpCodeCommands.push_back(&CPU::_CB3C);
	mCBOpCodeCommands.push_back(&CPU::_CB3D);
	mCBOpCodeCommands.push_back(&CPU::_CB3E);
	mCBOpCodeCommands.push_back(&CPU::_CB3F);

	// Opcodes 0xCB4X
	mCBOpCodeCommands.push_back(&CPU::_CB40);
	mCBOpCodeCommands.push_back(&CPU::_CB41);
	mCBOpCodeCommands.push_back(&CPU::_CB42);
	mCBOpCodeCommands.push_back(&CPU::_CB43);
	mCBOpCodeCommands.push_back(&CPU::_CB44);
	mCBOpCodeCommands.push_back(&CPU::_CB45);
	mCBOpCodeCommands.push_back(&CPU::_CB46);
	mCBOpCodeCommands.push_back(&CPU::_CB47);
	mCBOpCodeCommands.push_back(&CPU::_CB48);
	mCBOpCodeCommands.push_back(&CPU::_CB49);
	mCBOpCodeCommands.push_back(&CPU::_CB4A);
	mCBOpCodeCommands.push_back(&CPU::_CB4B);
	mCBOpCodeCommands.push_back(&CPU::_CB4C);
	mCBOpCodeCommands.push_back(&CPU::_CB4D);
	mCBOpCodeCommands.push_back(&CPU::_CB4E);
	mCBOpCodeCommands.push_back(&CPU::_CB4F);

	// Opcodes 0xCB5X
	mCBOpCodeCommands.push_back(&CPU::_CB50);
	mCBOpCodeCommands.push_back(&CPU::_CB51);
	mCBOpCodeCommands.push_back(&CPU::_CB52);
	mCBOpCodeCommands.push_back(&CPU::_CB53);
	mCBOpCodeCommands.push_back(&CPU::_CB54);
	mCBOpCodeCommands.push_back(&CPU::_CB55);
	mCBOpCodeCommands.push_back(&CPU::_CB56);
	mCBOpCodeCommands.push_back(&CPU::_CB57);
	mCBOpCodeCommands.push_back(&CPU::_CB58);
	mCBOpCodeCommands.push_back(&CPU::_CB59);
	mCBOpCodeCommands.push_back(&CPU::_CB5A);
	mCBOpCodeCommands.push_back(&CPU::_CB5B);
	mCBOpCodeCommands.push_back(&CPU::_CB5C);
	mCBOpCodeCommands.push_back(&CPU::_CB5D);
	mCBOpCodeCommands.push_back(&CPU::_CB5E);
	mCBOpCodeCommands.push_back(&CPU::_CB5F);

	// Opcodes 0xCB6X
	mCBOpCodeCommands.push_back(&CPU::_CB60);
	mCBOpCodeCommands.push_back(&CPU::_CB61);
	mCBOpCodeCommands.push_back(&CPU::_CB62);
	mCBOpCodeCommands.push_back(&CPU::_CB63);
	mCBOpCodeCommands.push_back(&CPU::_CB64);
	mCBOpCodeCommands.push_back(&CPU::_CB65);
	mCBOpCodeCommands.push_back(&CPU::_CB66);
	mCBOpCodeCommands.push_back(&CPU::_CB67);
	mCBOpCodeCommands.push_back(&CPU::_CB68);
	mCBOpCodeCommands.push_back(&CPU::_CB69);
	mCBOpCodeCommands.push_back(&CPU::_CB6A);
	mCBOpCodeCommands.push_back(&CPU::_CB6B);
	mCBOpCodeCommands.push_back(&CPU::_CB6C);
	mCBOpCodeCommands.push_back(&CPU::_CB6D);
	mCBOpCodeCommands.push_back(&CPU::_CB6E);
	mCBOpCodeCommands.push_back(&CPU::_CB6F);

	// Opcodes 0xCB7X
	mCBOpCodeCommands.push_back(&CPU::_CB70);
	mCBOpCodeCommands.push_back(&CPU::_CB71);
	mCBOpCodeCommands.push_back(&CPU::_CB72);
	mCBOpCodeCommands.push_back(&CPU::_CB73);
	mCBOpCodeCommands.push_back(&CPU::_CB74);
	mCBOpCodeCommands.push_back(&CPU::_CB75);
	mCBOpCodeCommands.push_back(&CPU::_CB76);
	mCBOpCodeCommands.push_back(&CPU::_CB77);
	mCBOpCodeCommands.push_back(&CPU::_CB78);
	mCBOpCodeCommands.push_back(&CPU::_CB79);
	mCBOpCodeCommands.push_back(&CPU::_CB7A);
	mCBOpCodeCommands.push_back(&CPU::_CB7B);
	mCBOpCodeCommands.push_back(&CPU::_CB7C);
	mCBOpCodeCommands.push_back(&CPU::_CB7D);
	mCBOpCodeCommands.push_back(&CPU::_CB7E);
	mCBOpCodeCommands.push_back(&CPU::_CB7F);

	// Opcodes 0xCB8X
	mCBOpCodeCommands.push_back(&CPU::_CB90);
	mCBOpCodeCommands.push_back(&CPU::_CB91);
	mCBOpCodeCommands.push_back(&CPU::_CB92);
	mCBOpCodeCommands.push_back(&CPU::_CB93);
	mCBOpCodeCommands.push_back(&CPU::_CB94);
	mCBOpCodeCommands.push_back(&CPU::_CB95);
	mCBOpCodeCommands.push_back(&CPU::_CB96);
	mCBOpCodeCommands.push_back(&CPU::_CB97);
	mCBOpCodeCommands.push_back(&CPU::_CB98);
	mCBOpCodeCommands.push_back(&CPU::_CB99);
	mCBOpCodeCommands.push_back(&CPU::_CB9A);
	mCBOpCodeCommands.push_back(&CPU::_CB9B);
	mCBOpCodeCommands.push_back(&CPU::_CB9C);
	mCBOpCodeCommands.push_back(&CPU::_CB9D);
	mCBOpCodeCommands.push_back(&CPU::_CB9E);
	mCBOpCodeCommands.push_back(&CPU::_CB9F);

	// Opcodes 0xCBAX
	mCBOpCodeCommands.push_back(&CPU::_CBA0);
	mCBOpCodeCommands.push_back(&CPU::_CBA1);
	mCBOpCodeCommands.push_back(&CPU::_CBA2);
	mCBOpCodeCommands.push_back(&CPU::_CBA3);
	mCBOpCodeCommands.push_back(&CPU::_CBA4);
	mCBOpCodeCommands.push_back(&CPU::_CBA5);
	mCBOpCodeCommands.push_back(&CPU::_CBA6);
	mCBOpCodeCommands.push_back(&CPU::_CBA7);
	mCBOpCodeCommands.push_back(&CPU::_CBA8);
	mCBOpCodeCommands.push_back(&CPU::_CBA9);
	mCBOpCodeCommands.push_back(&CPU::_CBAA);
	mCBOpCodeCommands.push_back(&CPU::_CBAB);
	mCBOpCodeCommands.push_back(&CPU::_CBAC);
	mCBOpCodeCommands.push_back(&CPU::_CBAD);
	mCBOpCodeCommands.push_back(&CPU::_CBAE);
	mCBOpCodeCommands.push_back(&CPU::_CBAF);

	// Opcodes 0xCBBX
	mCBOpCodeCommands.push_back(&CPU::_CBB0);
	mCBOpCodeCommands.push_back(&CPU::_CBB1);
	mCBOpCodeCommands.push_back(&CPU::_CBB2);
	mCBOpCodeCommands.push_back(&CPU::_CBB3);
	mCBOpCodeCommands.push_back(&CPU::_CBB4);
	mCBOpCodeCommands.push_back(&CPU::_CBB5);
	mCBOpCodeCommands.push_back(&CPU::_CBB6);
	mCBOpCodeCommands.push_back(&CPU::_CBB7);
	mCBOpCodeCommands.push_back(&CPU::_CBB8);
	mCBOpCodeCommands.push_back(&CPU::_CBB9);
	mCBOpCodeCommands.push_back(&CPU::_CBBA);
	mCBOpCodeCommands.push_back(&CPU::_CBBB);
	mCBOpCodeCommands.push_back(&CPU::_CBBC);
	mCBOpCodeCommands.push_back(&CPU::_CBBD);
	mCBOpCodeCommands.push_back(&CPU::_CBBE);
	mCBOpCodeCommands.push_back(&CPU::_CBBF);

	// Opcodes 0xCBCX
	mCBOpCodeCommands.push_back(&CPU::_CBC0);
	mCBOpCodeCommands.push_back(&CPU::_CBC1);
	mCBOpCodeCommands.push_back(&CPU::_CBC2);
	mCBOpCodeCommands.push_back(&CPU::_CBC3);
	mCBOpCodeCommands.push_back(&CPU::_CBC4);
	mCBOpCodeCommands.push_back(&CPU::_CBC5);
	mCBOpCodeCommands.push_back(&CPU::_CBC6);
	mCBOpCodeCommands.push_back(&CPU::_CBC7);
	mCBOpCodeCommands.push_back(&CPU::_CBC8);
	mCBOpCodeCommands.push_back(&CPU::_CBC9);
	mCBOpCodeCommands.push_back(&CPU::_CBCA);
	mCBOpCodeCommands.push_back(&CPU::_CBCB);
	mCBOpCodeCommands.push_back(&CPU::_CBCC);
	mCBOpCodeCommands.push_back(&CPU::_CBCD);
	mCBOpCodeCommands.push_back(&CPU::_CBCE);
	mCBOpCodeCommands.push_back(&CPU::_CBCF);

	// Opcodes 0xCBDX
	mCBOpCodeCommands.push_back(&CPU::_CBD0);
	mCBOpCodeCommands.push_back(&CPU::_CBD1);
	mCBOpCodeCommands.push_back(&CPU::_CBD2);
	mCBOpCodeCommands.push_back(&CPU::_CBD3);
	mCBOpCodeCommands.push_back(&CPU::_CBD4);
	mCBOpCodeCommands.push_back(&CPU::_CBD5);
	mCBOpCodeCommands.push_back(&CPU::_CBD6);
	mCBOpCodeCommands.push_back(&CPU::_CBD7);
	mCBOpCodeCommands.push_back(&CPU::_CBD8);
	mCBOpCodeCommands.push_back(&CPU::_CBD9);
	mCBOpCodeCommands.push_back(&CPU::_CBDA);
	mCBOpCodeCommands.push_back(&CPU::_CBDB);
	mCBOpCodeCommands.push_back(&CPU::_CBDC);
	mCBOpCodeCommands.push_back(&CPU::_CBDD);
	mCBOpCodeCommands.push_back(&CPU::_CBDE);
	mCBOpCodeCommands.push_back(&CPU::_CBDF);

	// Opcodes 0xCBEX
	mCBOpCodeCommands.push_back(&CPU::_CBE0);
	mCBOpCodeCommands.push_back(&CPU::_CBE1);
	mCBOpCodeCommands.push_back(&CPU::_CBE2);
	mCBOpCodeCommands.push_back(&CPU::_CBE3);
	mCBOpCodeCommands.push_back(&CPU::_CBE4);
	mCBOpCodeCommands.push_back(&CPU::_CBE5);
	mCBOpCodeCommands.push_back(&CPU::_CBE6);
	mCBOpCodeCommands.push_back(&CPU::_CBE7);
	mCBOpCodeCommands.push_back(&CPU::_CBE8);
	mCBOpCodeCommands.push_back(&CPU::_CBE9);
	mCBOpCodeCommands.push_back(&CPU::_CBEA);
	mCBOpCodeCommands.push_back(&CPU::_CBEB);
	mCBOpCodeCommands.push_back(&CPU::_CBEC);
	mCBOpCodeCommands.push_back(&CPU::_CBED);
	mCBOpCodeCommands.push_back(&CPU::_CBEE);
	mCBOpCodeCommands.push_back(&CPU::_CBEF);

	// Opcodes 0xCBFX
	mCBOpCodeCommands.push_back(&CPU::_CBF0);
	mCBOpCodeCommands.push_back(&CPU::_CBF1);
	mCBOpCodeCommands.push_back(&CPU::_CBF2);
	mCBOpCodeCommands.push_back(&CPU::_CBF3);
	mCBOpCodeCommands.push_back(&CPU::_CBF4);
	mCBOpCodeCommands.push_back(&CPU::_CBF5);
	mCBOpCodeCommands.push_back(&CPU::_CBF6);
	mCBOpCodeCommands.push_back(&CPU::_CBF7);
	mCBOpCodeCommands.push_back(&CPU::_CBF8);
	mCBOpCodeCommands.push_back(&CPU::_CBF9);
	mCBOpCodeCommands.push_back(&CPU::_CBFA);
	mCBOpCodeCommands.push_back(&CPU::_CBFB);
	mCBOpCodeCommands.push_back(&CPU::_CBFC);
	mCBOpCodeCommands.push_back(&CPU::_CBFD);
	mCBOpCodeCommands.push_back(&CPU::_CBFE);
	mCBOpCodeCommands.push_back(&CPU::_CBFF);
}