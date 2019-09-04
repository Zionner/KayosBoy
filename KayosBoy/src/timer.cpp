#include "timer.hpp"

Timer::Timer(Memory& mem) :
	mMemory(mem),
	mIsTimerEnabled(false),
	mFrequencyDividerMode(TimerFrequencyDivider::TFD_4096),
	mLastFrequencyDividerMode(TimerFrequencyDivider::TFD_4096),
	mCycleCounter(0x00)
{

}

void Timer::Tick(uint64_t elapsedCycles)
{
	uint8_t timerControlByte = GetTimerControl();
	mIsTimerEnabled = timerControlByte & (1 << 2);

	if (!mIsTimerEnabled)
	{
		return;
	}

	mFrequencyDividerMode = static_cast<TimerFrequencyDivider>((timerControlByte & (1 << 0)) | (timerControlByte & (1 << 1)));

	if (mFrequencyDividerMode != mLastFrequencyDividerMode)
	{
		mLastFrequencyDividerMode = mFrequencyDividerMode;
		mCycleCounter = 0;
	}

	SetDividerRegister(GetDividerRegister() + static_cast<uint8_t>(elapsedCycles));

	mCycleCounter += elapsedCycles;

	if (mFrequencyDividerMode == TFD_4096 && mCycleCounter >= 255 ||
		mFrequencyDividerMode == TFD_16386 && mCycleCounter >= 63 ||
		mFrequencyDividerMode == TFD_65536 && mCycleCounter >= 15 ||
		mFrequencyDividerMode == TFD_262144 && mCycleCounter >= 3)
	{
		mCycleCounter = 0;

		uint8_t interrupts = mMemory.ReadByteAtPointer(KayosBoyPtr(ImportantMemoryAddresses::IMA_InterruptFlagRegister));
		mMemory.WriteByteAtPointer(KayosBoyPtr(ImportantMemoryAddresses::IMA_InterruptFlagRegister), static_cast<uint8_t>(interrupts | (2 >> 1))); // set bit 2 to 1

		uint8_t timerCounter = GetTimerCounter();

		if (timerCounter >= 255)
		{
			SetTimerCounter(GetTimerModulo());
		}
		else
		{
			SetTimerCounter(timerCounter + 1);
		}
	}

}

void Timer::SetDividerRegister(uint8_t val)
{
	mMemory.WriteByteAtPointer(KayosBoyPtr(TimerRegisterAddresses::TRA_Divider), val);
}

void Timer::SetTimerCounter(uint8_t val)
{
	mMemory.WriteByteAtPointer(KayosBoyPtr(TimerRegisterAddresses::TRA_TimerCounter), val);
}

void Timer::SetTimerModulo(uint8_t val)
{
	mMemory.WriteByteAtPointer(KayosBoyPtr(TimerRegisterAddresses::TRA_TimerModulo), val);
}

void Timer::SetTimerControl(uint8_t val)
{
	mMemory.WriteByteAtPointer(KayosBoyPtr(TimerRegisterAddresses::TRA_TimerControl), val);
}

uint8_t Timer::GetDividerRegister()
{
	return mMemory.ReadByteAtPointer(KayosBoyPtr(TimerRegisterAddresses::TRA_Divider));
}

uint8_t Timer::GetTimerCounter()
{
	return mMemory.ReadByteAtPointer(KayosBoyPtr(TimerRegisterAddresses::TRA_TimerCounter));
}

uint8_t Timer::GetTimerModulo()
{
	return mMemory.ReadByteAtPointer(KayosBoyPtr(TimerRegisterAddresses::TRA_TimerModulo));
}

uint8_t Timer::GetTimerControl()
{
	return mMemory.ReadByteAtPointer(KayosBoyPtr(TimerRegisterAddresses::TRA_TimerControl));
}