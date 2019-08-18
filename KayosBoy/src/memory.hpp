#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "registers.hpp"
#include "Cartridge.hpp"

enum MemoryState : uint8_t
{
	MS_BootRomLoaded = 0x00,
	MS_CartridgeLoaded = 0x01,
};

class Memory
{
	public:
		Memory(Cartridge& cart);

		uint8_t ReadByteAtPointer(KayosBoyPtr ptr);
		uint16_t ReadTwoBytesAtPointer(KayosBoyPtr ptr);

		void WriteByteAtPointer(KayosBoyPtr ptr, uint8_t val);
		void WriteTwoBytesAtPointer(KayosBoyPtr ptr, uint16_t val);

	protected:
		Cartridge& mCartridge;
};

#endif // _MEMORY_H_