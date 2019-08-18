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
		Memory(char* const pathToBootRom, Cartridge& cart);

		uint8_t ReadByteAtPointer(KayosBoyPtr ptr);
		uint16_t ReadTwoBytesAtPointer(KayosBoyPtr ptr);

		void WriteByteAtPointer(KayosBoyPtr ptr, uint8_t val);
		void WriteTwoBytesAtPointer(KayosBoyPtr ptr, uint16_t val);

	protected:
		bool LoadBootROM(char* path);
		bool IsRunningBootRom();

		uint16_t ReadTwoBytesFromVector(std::vector<uint8_t>& vec, uint16_t addr);
		void WriteTwoBytesIntoVector(std::vector<uint8_t>& vec, uint16_t addr, uint16_t val);

		Cartridge& mCartridge;

		// We're loading these from files instead of from a const value
		// Because it allows us to nicely support multiple boot ROMs (and custom boot ROMS).
		// Main reason for doing this: Supporting DMG & GBC Roms. Maybe GBA later on if I want to go that far.
		std::vector<uint8_t> mBootRom;

		std::vector<uint8_t>* mVRam; // Bankable in GBC.
		std::vector<uint8_t> mStaticWRam;
		std::vector<uint8_t>* mBankWRam; // Only bankable on GBC.
		std::vector<uint8_t> mOAM;
		std::vector<uint8_t> mUnused; // Seems to be unused. Does have some specific behaviours that differ between models, but won't implement this for now.
		std::vector<uint8_t> mIORegisters;
		std::vector<uint8_t> mHRAM;
		uint8_t mInterruptRegister;
};

#endif // _MEMORY_H_