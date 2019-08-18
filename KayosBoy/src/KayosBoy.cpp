#include "GameBoy.hpp"
#include "KayosBoyUtils.hpp"

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

int main(int argc, char* argv[])
{
	uint8_t index = 0;

#ifdef _WIN32
	if (IsDebuggerPresent())
	{
		index++;
	}
#endif

	if (argc < (2 + index))
	{
		printf("Did not supply require arguments. Need a path to boot rom and cartridge rom. Optional cartridge ram.");
	}

	if (argc == (2 + index))
	{
		GameBoy cpuTest(argv[index], argv[index + 1]);
	}
	else if (argc > (2 + index))
	{
		GameBoy cpuTest(argv[index], argv[index + 1], argv[index + 2]);
	}
	

	return 1;
}