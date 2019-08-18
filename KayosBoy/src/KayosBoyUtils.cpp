#include "KayosBoyUtils.hpp"

size_t LoadBinaryFile(char* const path, uint8_t** ptr)
{
	if (path == nullptr)
	{
		return false;
	}

	std::ifstream file;
	file.open(path, std::ios::in | std::ios::binary | std::ios::ate);

	if (file.is_open())
	{
		size_t size = file.tellg();
		(*ptr) = new uint8_t[size]; // Destroyed 
		file.seekg(0, std::ios::beg);
		file.read((char*)(*ptr), size);
		file.close();

		return size;
	}

	return 0;
}