#include "memory.hpp"

Memory::Memory(Cartridge& cart) :
	mCartridge(cart)
{

}

uint8_t Memory::ReadByteAtPointer(KayosBoyPtr ptr)
{
	if	(ptr.GetPointerVal() <= 0x7FFF 
		|| (ptr.GetPointerVal() >= 0xA000 && ptr.GetPointerVal() <= 0xBFFF))
	{
		return mCartridge.read(ptr);
	}
	else // internal memory (VRAM, WRAM, HRAM ect)
	{
		printf("Internal Memory unimplemented");
	}

	return 0;
}

uint16_t Memory::ReadTwoBytesAtPointer(KayosBoyPtr ptr)
{
	if	(ptr.GetPointerVal() <= 0x7FFF 
		|| (ptr.GetPointerVal() >= 0xA000 && ptr.GetPointerVal() <= 0xBFFF))
	{
		return mCartridge.readTwoBytes(ptr);
	}
	else // internal memory (VRAM, WRAM, HRAM ect)
	{
		printf("Internal Memory unimplemented");
	}

	return 0;
}

void Memory::WriteByteAtPointer(KayosBoyPtr ptr, uint8_t val)
{
	if	(ptr.GetPointerVal() <= 0x7FFF 
		|| (ptr.GetPointerVal() >= 0xA000 && ptr.GetPointerVal() <= 0xBFFF))
	{
		mCartridge.write(ptr, val);
	}
	else // internal memory (VRAM, WRAM, HRAM ect)
	{
		printf("Internal Memory unimplemented");
	}
}

void Memory::WriteTwoBytesAtPointer(KayosBoyPtr ptr, uint16_t val)
{
	if	(ptr.GetPointerVal() <= 0x7FFF || 
		(ptr.GetPointerVal() >= 0xA000 && ptr.GetPointerVal() <= 0xBFFF))
	{
		mCartridge.writeTwoBytes(ptr, val);
	}
	else // internal memory (VRAM, WRAM, HRAM ect)
	{
		printf("Internal Memory unimplemented");
	}
}