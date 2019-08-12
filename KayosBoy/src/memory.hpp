#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "registers.hpp"

class Memory
{
	public:
		Memory();

		uint8_t ReadByteAtPointer(KayosBoyPtr ptr);
		uint16_t ReadTwoBytesAtPointer(KayosBoyPtr ptr);
		uint8_t* GetSysPointerFromBoyPointer(KayosBoyPtr ptr);

		void WriteByteAtPointer(KayosBoyPtr ptr, uint8_t val);
		void WriteTwoBytesAtPointer(KayosBoyPtr ptr, uint16_t val);

	protected:
		
};

#endif // _MEMORY_H_