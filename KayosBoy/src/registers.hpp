#ifndef _REGISTERS_H_
#define _REGISTERS_H_

#include <stdint.h>

struct RegisterByteMemory
{
	bool Bit00 : 1;
	bool Bit01 : 1;
	bool Bit02 : 1;
	bool Bit03 : 1;
	bool Bit04 : 1;
	bool Bit05 : 1;
	bool Bit06 : 1;
	bool Bit07 : 1;
};

struct RegisterTwoByteMemory : RegisterByteMemory
{
	bool Bit08 : 1;
	bool Bit09 : 1;
	bool Bit10 : 1;
	bool Bit11 : 1;
	bool Bit12 : 1;
	bool Bit13 : 1;
	bool Bit14 : 1;
	bool Bit15 : 1;
};

struct FlagRegistryMemory
{
	bool ZeroFlag : 1;
	bool SubtractFlag : 1;
	bool HalfCarryFlag : 1;
	bool CarryFlag : 1;
	bool UnusedBits : 4;
};

union RegisterMemory
{
	uint8_t ByteMemory;
	RegisterByteMemory StructuredByteMemory;
	FlagRegistryMemory StructuredFlagMemory;
};

union TwoByteRegisterMemory
{
	uint16_t PairedBytes;
	RegisterTwoByteMemory StructuredByteMemory;
};

template <class T>
class Register
{
	public:
		Register() {}
		~Register() {}
		T& operator=(const T&) = delete;
		Register (const Register&) = delete;
};

class KayosBoyPtr
{
public:
	KayosBoyPtr();
	KayosBoyPtr(uint16_t addr);
	KayosBoyPtr(class PairedByteRegister& addr);
	KayosBoyPtr(class TwoByteRegister& addr);

	void UpdatePointerVal(uint16_t val);
	uint16_t GetPointerVal() const;

	bool operator==(KayosBoyPtr otherPtr) const;
	KayosBoyPtr operator+(KayosBoyPtr otherPtr) const;
	KayosBoyPtr operator-(KayosBoyPtr otherPtr) const;


private:
	uint16_t mAddress;
};

class ByteRegister : public Register<ByteRegister>
{
public:

	void SetRegister(uint8_t value);
	RegisterMemory GetRegisterValue() const;

	void SetRegisterBit(uint8_t bit, bool bitVal);
	bool GetRegisterBit(uint8_t bit) const;

	void IncrementRegister();
	void DecrementRegister();

protected:
	RegisterMemory mRegisterMem;
};

class FlagRegister : public ByteRegister
{
	bool GetZeroFlag();
	void SetZeroFlag(bool val);

	bool GetSubtractFlag();
	void SetSubtractFlag(bool val);

	bool GetHalfCarryFlag();
	void SetHalfCarryFlag(bool val);

	bool GetCarryFlag();
	void SetCarryFlag(bool val);
};


static_assert(sizeof(RegisterByteMemory) == 1, "RegisterByteMemory Memory Wrong Size ");
static_assert(sizeof(FlagRegistryMemory) == 1, "FlagRegistryMemory Memory Wrong Size");
static_assert(sizeof(RegisterMemory) == 1, "RegisterMemory Memory Wrong Size");

class PairedByteRegister : public Register<PairedByteRegister>
{
public:
	PairedByteRegister(ByteRegister& highRegister, ByteRegister& lowRegister);
	PairedByteRegister(ByteRegister& highRegister, FlagRegister& lowRegister);

	void SetRegister(uint16_t value);
	TwoByteRegisterMemory GetRegisterValue() const;

	void SetRegisterBit(uint8_t bit, bool bitVal);
	bool GetRegisterBit(uint8_t bit) const;

	RegisterMemory UpperBits();
	RegisterMemory LowerBits();

	void Increment();
	void Decrement();

	KayosBoyPtr& RegisterAsAddress();

private:
	ByteRegister& LowerRegister;
	ByteRegister& HigherRegister;
	KayosBoyPtr mRegisterAsAddress;
};

class TwoByteRegister : public Register<PairedByteRegister>
{
public:

	void SetRegister(uint16_t value);
	TwoByteRegisterMemory GetRegisterValue() const;

	void SetRegisterBit(uint8_t bit, bool bitVal);
	bool GetRegisterBit(uint8_t bit) const;

	RegisterMemory UpperBits();
	RegisterMemory LowerBits();

	void Increment();
	void Decrement();

	KayosBoyPtr& RegisterAsAddress();

private:
	TwoByteRegisterMemory mRegisterMem;
	KayosBoyPtr mRegisterAsAddress;
};

#endif // _REGISTERS_H_