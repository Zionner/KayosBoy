#include "gpu.hpp"

GPU::GPU(Memory& mem) :
	mMemory(mem)
{

}

void GPU::Tick(uint64_t elapsedTicks)
{
	LCDControlRegister controlreg = GetLCDControlRegisterFromMemory();
	LCDStatRegister statreg = GetLCDStatRegister();
	uint8_t interrupts = mMemory.ReadByteAtPointer(KayosBoyPtr(ImportantMemoryAddresses::IMA_InterruptFlagRegister));

	mTickCount += elapsedTicks;

	switch (statreg.ScreenMode)
	{
	case VideoMode::VM_HBlank:
		if (mTickCount >= HBlankClockLength)
		{
			mTickCount = mTickCount % HBlankClockLength;

			uint8_t currentScanLine = mMemory.ReadByteAtPointer(KayosBoyPtr(ImportantMemoryAddresses::IMA_CurrentScanline));

			if (IsLCDDisplayEnabled())
			{
				// Render background & windows here.
			}

			currentScanLine++;
			mMemory.WriteByteAtPointer(KayosBoyPtr(ImportantMemoryAddresses::IMA_CurrentScanline), currentScanLine);

			if (currentScanLine >= ScanLineCount)
			{
				statreg.ScreenMode = VideoMode::VM_VBlank;
				mMemory.WriteByteAtPointer(KayosBoyPtr(ImportantMemoryAddresses::IMA_InterruptFlagRegister), static_cast<uint8_t>(interrupts | (0 >> 1))); // set bit 0 to 1
			}
			else
			{
				statreg.ScreenMode = VideoMode::VM_OAM;
			}
		}
		break;
	case VideoMode::VM_VBlank:
		if (mTickCount >= ScanlineClockLength)
		{
			uint8_t currentScanLine = mMemory.ReadByteAtPointer(KayosBoyPtr(ImportantMemoryAddresses::IMA_CurrentScanline));
			currentScanLine++;
			mMemory.WriteByteAtPointer(KayosBoyPtr(ImportantMemoryAddresses::IMA_CurrentScanline), currentScanLine);

			mTickCount = mTickCount % ScanlineClockLength;

			if (currentScanLine == 154)
			{
				if (SpriteDisplayEnabled())
				{
					// Sprite Rendering.
				}

				// Framebuffer to texture writes here.
				mFrameCounter++;
				printf("\rFrame Counter: 0x%04x", mFrameCounter);
				statreg.ScreenMode = VideoMode::VM_OAM;
			}
		}
		break;
	case VideoMode::VM_OAM:
		if (mTickCount >= OAMClockLength)
		{
			mTickCount = mTickCount % OAMClockLength;
			statreg.ScreenMode = VideoMode::VM_Transfer;
		}
		break;
	case VideoMode::VM_Transfer:
		if (mTickCount >= VRAMClockLength)
		{
			mTickCount = mTickCount % VRAMClockLength;
			statreg.ScreenMode = VideoMode::VM_HBlank;

			bool lycinterrupt = statreg.LYCInteruptEnable;
			bool lyc = mMemory.ReadByteAtPointer(KayosBoyPtr(ImportantMemoryAddresses::IMA_LYCompare)) == mMemory.ReadByteAtPointer(KayosBoyPtr(ImportantMemoryAddresses::IMA_CurrentScanline));

			if ((lycinterrupt && lyc) || statreg.ModeZeroHBlankCheckEnable)
			{
				mMemory.WriteByteAtPointer(KayosBoyPtr(ImportantMemoryAddresses::IMA_InterruptFlagRegister), static_cast<uint8_t>(interrupts | (1 >> 1))); // set bit 1 to 1
			}

			statreg.LYCComparisonSignal = lyc;
		}
		break;
	}

	UpdateLCDStatRegister(statreg);
}

LCDControlRegister GPU::GetLCDControlRegisterFromMemory()
{
	LCDControlRegisterUnion controlRegisterByte;
	controlRegisterByte.RegisterData = mMemory.ReadByteAtPointer(KayosBoyPtr(ImportantMemoryAddresses::IMA_LCDControlRegister));

	return controlRegisterByte.StructuredRegister;
}

LCDStatRegister GPU::GetLCDStatRegister()
{
	LCDStatRegisterUnion statRegisterByte;
	statRegisterByte.RegisterData = mMemory.ReadByteAtPointer(KayosBoyPtr(ImportantMemoryAddresses::IMA_LCDStat));

	return statRegisterByte.StructuredRegister;
}

void GPU::UpdateLCDStatRegister(LCDStatRegister newStatData)
{
	LCDStatRegisterUnion statRegisterByte;
	statRegisterByte.StructuredRegister = newStatData;

	mMemory.WriteByteAtPointer(KayosBoyPtr(ImportantMemoryAddresses::IMA_LCDStat), statRegisterByte.RegisterData);
}

bool GPU::IsLCDDisplayEnabled()
{
	LCDControlRegister reg = GetLCDControlRegisterFromMemory();

	return reg.LCDPowerEnabled;
}

bool GPU::WindowTileMapDisplaySelect()
{
	LCDControlRegister reg = GetLCDControlRegisterFromMemory();

	return reg.WindowTileMpa;
}

bool GPU::IsWindowDisplayEnabled()
{
	LCDControlRegister reg = GetLCDControlRegisterFromMemory();

	return reg.WindowEnabled;
}

bool GPU::BackgroundAndWindowTileDataSelect()
{
	LCDControlRegister reg = GetLCDControlRegisterFromMemory();

	return reg.BackgroundWindowTileSet;
}

bool GPU::SpriteSize()
{
	LCDControlRegister reg = GetLCDControlRegisterFromMemory();

	return reg.SpriteSize;
}

bool GPU::SpriteDisplayEnabled()
{
	LCDControlRegister reg = GetLCDControlRegisterFromMemory();

	return reg.SpritesEnabled;
}

bool GPU::BackgroundandWindowDisplayPriority()
{
	LCDControlRegister reg = GetLCDControlRegisterFromMemory();

	return reg.BackgroundEnabled;
}