#include "registers.hpp"

ByteRegister::ByteRegister(uint8_t val)
{
	mRegisterMem.ByteMemory = val;
}

void ByteRegister::SetRegister(uint8_t value)
{
	mRegisterMem.ByteMemory = value;
}

RegisterMemory ByteRegister::GetRegisterValue() const
{
	return mRegisterMem;
}

void ByteRegister::SetRegisterBit(uint8_t bit, bool bitVal)
{
	mRegisterMem.ByteMemory |= (bitVal << bit);
}

bool ByteRegister::GetRegisterBit(uint8_t bit) const
{
	return (mRegisterMem.ByteMemory & (1 << bit)) != 0;
}

void ByteRegister::IncrementRegister()
{
	mRegisterMem.ByteMemory += 1;
}

void ByteRegister::DecrementRegister()
{
	mRegisterMem.ByteMemory -= 1;
}

FlagRegister::FlagRegister(uint8_t val) :
	ByteRegister(val)
{

}

bool FlagRegister::GetZeroFlag()
{
	return mRegisterMem.StructuredFlagMemory.ZeroFlag;
}

void FlagRegister::SetZeroFlag(bool val)
{
	mRegisterMem.StructuredFlagMemory.ZeroFlag = val;
}

bool FlagRegister::GetSubtractFlag()
{
	return mRegisterMem.StructuredFlagMemory.SubtractFlag;
}

void FlagRegister::SetSubtractFlag(bool val)
{
	mRegisterMem.StructuredFlagMemory.SubtractFlag = val;
}

bool FlagRegister::GetHalfCarryFlag()
{
	return mRegisterMem.StructuredFlagMemory.HalfCarryFlag;
}

void FlagRegister::SetHalfCarryFlag(bool val)
{
	mRegisterMem.StructuredFlagMemory.HalfCarryFlag = val;
}

bool FlagRegister::GetCarryFlag()
{
	return mRegisterMem.StructuredFlagMemory.CarryFlag;
}

void FlagRegister::SetCarryFlag(bool val)
{
	mRegisterMem.StructuredFlagMemory.CarryFlag = val;
}

PairedByteRegister::PairedByteRegister(ByteRegister& highRegister, ByteRegister& lowRegister) :
	HigherRegister(highRegister),
	LowerRegister(lowRegister)
{
}

PairedByteRegister::PairedByteRegister(ByteRegister& highRegister, FlagRegister& lowRegister) :
	HigherRegister(highRegister),
	LowerRegister(lowRegister)
{

}

void PairedByteRegister::SetRegister(uint16_t value)
{
	LowerRegister.SetRegister(static_cast<uint8_t>(value));
	HigherRegister.SetRegister(static_cast<uint8_t>(value >> 8));
}

TwoByteRegisterMemory PairedByteRegister::GetRegisterValue() const
{
	uint16_t ret = (static_cast<uint16_t>(HigherRegister.GetRegisterValue().ByteMemory) << 8) 
					| static_cast<uint16_t>(LowerRegister.GetRegisterValue().ByteMemory);
	return TwoByteRegisterMemory{ ret };
}

void PairedByteRegister::SetRegisterBit(uint8_t bit, bool bitVal)
{
	// TODO: Double check, does this bitshift start at 0 or 1?
	if (bit > 7)
	{
		HigherRegister.SetRegisterBit(bit - 8, bitVal);
	}
	else
	{
		LowerRegister.SetRegisterBit(bit, bitVal);
	}
	
}

bool PairedByteRegister::GetRegisterBit(uint8_t bit) const
{
	// TODO: Double check, does this bitshift start at 0 or 1?
	if (bit > 7)
	{
		return HigherRegister.GetRegisterBit(bit - 8);
	}
	else
	{
		return LowerRegister.GetRegisterBit(bit);
	}
	 
}

RegisterMemory PairedByteRegister::UpperBits()
{
	return HigherRegister.GetRegisterValue();
}

RegisterMemory PairedByteRegister::LowerBits()
{
	return LowerRegister.GetRegisterValue();
}

void PairedByteRegister::Increment()
{
	SetRegister(GetRegisterValue().PairedBytes + 1);
}

void PairedByteRegister::Decrement()
{
	SetRegister(GetRegisterValue().PairedBytes - 1);
}

KayosBoyPtr& PairedByteRegister::RegisterAsAddress()
{
	mRegisterAsAddress.UpdatePointerVal(GetRegisterValue().PairedBytes);
	return mRegisterAsAddress;
}

void TwoByteRegister::SetRegister(uint16_t value)
{
	mRegisterMem.PairedBytes = value;
}

TwoByteRegisterMemory TwoByteRegister::GetRegisterValue() const
{
	return mRegisterMem;
}

void TwoByteRegister::SetRegisterBit(uint8_t bit, bool bitVal)
{
	mRegisterMem.PairedBytes |= (bitVal << bit);
}

bool TwoByteRegister::GetRegisterBit(uint8_t bit) const
{
	return (mRegisterMem.PairedBytes & (1 << bit)) != 0;
}

RegisterMemory TwoByteRegister::UpperBits()
{
	return RegisterMemory{ static_cast<uint8_t>(mRegisterMem.PairedBytes << 8) };
}

RegisterMemory TwoByteRegister::LowerBits()
{
	return RegisterMemory{ static_cast<uint8_t>(mRegisterMem.PairedBytes) };
}

void TwoByteRegister::Increment()
{
	mRegisterMem.PairedBytes += 1;
}

void TwoByteRegister::Decrement()
{
	mRegisterMem.PairedBytes -= 1;
}

KayosBoyPtr& TwoByteRegister::RegisterAsAddress()
{
	mRegisterAsAddress.UpdatePointerVal(GetRegisterValue().PairedBytes);
	return mRegisterAsAddress;
}

KayosBoyPtr::KayosBoyPtr() :
	mAddress(0)
{

}

KayosBoyPtr::KayosBoyPtr(uint16_t addr) :
	mAddress(addr)
{
}

KayosBoyPtr::KayosBoyPtr(PairedByteRegister& addr) :
	mAddress(addr.GetRegisterValue().PairedBytes)
{

}

KayosBoyPtr::KayosBoyPtr(TwoByteRegister& addr) :
	mAddress(addr.GetRegisterValue().PairedBytes)
{

}

void KayosBoyPtr::UpdatePointerVal(uint16_t val)
{
	mAddress = val;
}

uint16_t KayosBoyPtr::GetPointerVal() const
{
	return mAddress;
}

bool KayosBoyPtr::operator==(KayosBoyPtr otherPtr) const
{
	return GetPointerVal() == otherPtr.GetPointerVal();
}

KayosBoyPtr KayosBoyPtr::operator+(KayosBoyPtr otherPtr) const
{
	return KayosBoyPtr(mAddress + otherPtr.GetPointerVal());
}

KayosBoyPtr KayosBoyPtr::operator-(KayosBoyPtr otherPtr) const
{
	return KayosBoyPtr(mAddress - otherPtr.GetPointerVal());
}