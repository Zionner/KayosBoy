#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "registers.hpp"
#include "Cartridge.hpp"

enum ImportantMemoryAddresses : uint16_t
{
	IMA_BootRomEnd = 0x00FF,
	IMA_StartOfSwitchROM = 0x4000,
	IMA_EndOfSwitableROM = 0x7FFF,
	IMA_StartOfVRAM = 0x8000,
	IMA_EndOfVRAM = 0x9FFF,
	IMA_StartOfCartridgeRam = 0xA000,
	IMA_EndOfCartridgeRam = 0xBFFF,
	IMA_StartOfStaticWRAM = 0xC000,
	IMA_EndOfStaticWRAM = 0xCFFF,
	IMA_StartOfSwitchWRAM = 0xD000,
	IMA_EndOfSwitchWRAM = 0xDFFF,
	IMA_StartOfStaticWRAMEcho = 0xE000,
	IMA_EndOfStaticWRAMEcho = 0xEFFF,
	IMA_StartOfSwitchWRAMEcho = 0xF000,
	IMA_EndOfSwitchWRAMEcho = 0xFDFF,
	IMA_StartOfOAM = 0xFE00,
	IMA_EndOfOAM = 0xFE9F,
	IMA_StartOfUnused = 0xFEA0,
	IMA_EndOfUnused = 0xFEFF,
	IMA_StartOfIORegisters = 0xFF00,
	IMA_InterruptFlagRegister = 0xFF0F,
	IMA_LCDControlRegister = 0xFF40,
	IMA_LCDStat = 0xFF41,
	IMA_BackGroundScrollY = 0xFF42,
	IMA_BackGroundScrollX = 0xFF43,
	IMA_CurrentScanline = 0xFF44,
	IMA_LYCompare = 0xFF45,
	IMA_DMAAddress = 0xFF46,
	IMA_WindowPositionY = 0xFF4A,
	IMA_WindowPositionX = 0xFF4B,
	IMA_BootROMEnabledFlag = 0xFF50,
	IMA_HDMASourceHighByte = 0xFF51,				//
	IMA_HDMASourceLowByte = 0xFF52,					//
	IMA_HDMADestinationHighByte = 0xFF53,			// HDMA is GBC only
	IMA_HDMADestinationLowByte = 0xFF54,			//
	IMA_HDMALengthAndMode = 0xFF55,					//
	IMA_EndOfIORegisters = 0xFF7F,
	IMA_StartOfHRAM = 0xFF80,
	IMA_EndOfHRAM = 0xFFFE,
	IMA_InterruptEnableFlags = 0xFFFF
};

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
		uint16_t ReadTwoBytesFromTwoVectors(std::vector<uint8_t>& vec1, std::vector<uint8_t>& vec2, uint16_t addr);

		void WriteByteAtPointer(KayosBoyPtr ptr, uint8_t val);
		void WriteTwoBytesAtPointer(KayosBoyPtr ptr, uint16_t val);
		void WriteTwoBytesIntoTwoVectors(std::vector<uint8_t>& vec1, std::vector<uint8_t>& vec2, uint16_t addr, uint16_t val);

		void HandleDMA(uint64_t elapsedTicks);
		bool IsDMAInProgress();

		static const uint64_t DMACycleLength = 640;
		static const uint64_t DMASetupCycles = 8;

	protected:
		bool LoadBootROM(char* path);
		bool IsRunningBootRom();

		uint16_t ReadTwoBytesFromVector(std::vector<uint8_t>& vec, uint16_t addr);
		void WriteTwoBytesIntoVector(std::vector<uint8_t>& vec, uint16_t addr, uint16_t val);

		Cartridge& mCartridge;

		uint8_t mPreviousDMARegisterValue = 0x00;
		uint64_t mDMACycles = 0;

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
		std::vector<uint8_t> mInterruptRegister;
};

#endif // _MEMORY_H_