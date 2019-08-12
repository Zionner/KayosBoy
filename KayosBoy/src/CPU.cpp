#include "CPU.hpp"

CPU::CPU() :
	mRegisterAF(mRegisterA, mRegisterF),
	mRegisterBC(mRegisterB, mRegisterC),
	mRegisterDE(mRegisterD, mRegisterE),
	mRegisterHL(mRegisterH, mRegisterL)
{

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

// CALL
void CPU::CALL()
{

}

void CPU::CALL(uint8_t flagCondition)
{

}

// CFF
void CPU::CFF()
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

void CPU::JP(uint8_t flagCondition)
{

}

void CPU::JP(KayosBoyPtr& ptr)
{

}

// JR
void CPU::JR()
{

}

void CPU::JR(uint8_t flagCondition)
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

// RST
void CPU::RST(uint8_t offset)
{

}

// SCF
void CPU::SCF()
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