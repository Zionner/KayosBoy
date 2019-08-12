#ifndef _CARTRIDGE_H_
#define _CARTRIDGE_H_

#include "MBC.hpp"

enum CartridgeGameboyColourFlag : uint8_t
{
	CGBC_GB = 0x00,
	CGBC_GBC = 0x80
};

enum CartridgeSuperGameboyFlag : uint8_t
{
	CSGB_GB = 0x00,
	CSGB_SGB = 0x03
};

enum CartridgeReservedAddresses : uint16_t
{
	CRA_ExecutionEntryPoint = 0x0100,
	CRA_NintendoLogo = 0x0104,
	CRA_GameTitle = 0x0134,
	CRA_GBCFlag = 0x0143,
	CRA_LicenseHighNibble = 0x0144,
	CRA_LicenseLowNibble = 0x0145,
	CRA_SGBFlag = 0x0146,
	CRA_CartridgeTypeFlag = 0x0147,
	CRA_CartridgeRomSizeFlag = 0x0148,
	CRA_CartridgeRamSizeFlag = 0x0149,
	CRA_LocaleFlag = 0x014A,
	CRA_OldLicenseeCodeFlag = 0x014B,
	CRA_MaskRomVersionNumber = 0x014C,
	CRA_ComplimentCheck = 0x014D,
	CRA_Checksum = 0x014E
};



enum CartridgeRamSize : uint8_t
{
	CRAM_None = 0x00,
	CRAM_2KByte = 0x01,
	CRAM_8KByte = 0x02,
	CRAM_32KByte = 0x03,
	CRAM_128KByte = 0x04
};

enum CartridgeRomSize : uint8_t
{
	CROM_32KByte = 0x00,
	CROM_64KByte = 0x01,
	CROM_128KByte = 0x02,
	CROM_256KByte = 0x03,
	CROM_512KByte = 0x04,
	CROM_1024KByte = 0x05,
	CROM_2048KByte = 0x06,
	CROM_1127KByte = 0x52,
	CROM_1229KByte = 0x53,
	CROM_1536KByte = 0x54
};

enum CartridgeType : uint8_t
{
	CT_RomOnly = 0x00,
	CT_RomMBC1 = 0x01,
	CT_RomMBC1Ram = 0x02,
	CT_RomMBC1RamBatt = 0x03,
	CT_RomMBC2 = 0x05,
	CT_RomMBC2Battery = 0x06,
	CT_RomRam = 0x08,
	CT_RomRamBattery = 0x09,
	CT_RomMMM1 = 0x0B,
	CT_RomMMM1SRam = 0x0C,
	CT_RomMMM1SRamBatt = 0x0D,
	CT_RomMBC3TimerBatt = 0x0F,
	CT_RomMBC3TimerRamBatt = 0x10,
	CT_RomMBC3 = 0x11,
	CT_RomMBC3Ram = 0x12,
	CT_RomMBC3RamBatt = 0x13,
	CT_RomMBC5 = 0x19,
	CT_RomMBC5Ram = 0x1A,
	CT_RomMBC5RamBatt = 0x1B,
	CT_RomMBC5Rumble = 0x1C,
	CT_RomMBC5RumbleSRam = 0x1D,
	CT_RomMBC5RumbleSRamBatt = 0x1E,
	CT_PocketCamera = 0x1F,
	CT_BandaiTAMA5 = 0xFD,
	CT_HudsonHuC3 = 0xFE,
	CT_HudsonHuC1 = 0xFF
};

enum CartridgeLocalization
{
	CL_Japanese = 0x00,
	CL_AnywhereElse = 0x01
};

enum CartridgeOldLicenseeCode
{
	COLC_CheckNibbles = 0x33,
	COLC_Accolade = 0x79,
	COLC_Konami = 0xA4
};

struct CartridgeHeader
{
	uint8_t ExecutionStart[4]; // 0x0100-0x103
	uint8_t NintendoLogo[48]; // 0x0104-0x0133
	unsigned char GameTitle[16]; // 0x0134-0x0142
	CartridgeGameboyColourFlag GameboyColourFlag; // 0x0143
	uint8_t LicenseHighNibble; // 0x0144
	uint8_t LicenseLowNibble; // 0x0145
	CartridgeSuperGameboyFlag SuperGameboyFlag; // 0x0146
	CartridgeType CartridgeTypeFlag; // 0x0147
	CartridgeRomSize CartridgeRomSizeFlag; // 0x0148
	CartridgeRamSize CartridgeRamSizeFlag; // 0x0149
	CartridgeLocalization CartridgeLocalizationFlag; // 0x014A
	CartridgeOldLicenseeCode CartridgeOldLicenseeFlag; // 0x014B
	uint8_t CartridgeRomVersionFlag; // 0x014C
	uint8_t CartridgeComplementCheck; // 0x014D
	uint16_t CartridgeChecksum; // 0x014E-0x014F
};

class Cartridge
{
public:
	Cartridge();

protected:
	CartridgeHeader mCartridgeHeader;
	void* mCartridgeRom;
	void* mCartridgeRam;
	BaseMBC* mCartridgeMBC;
};

#endif // _CARTRIDGE_H_