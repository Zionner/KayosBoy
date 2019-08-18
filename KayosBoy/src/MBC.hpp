#ifndef _MBC_H_
#define _MBC_H_

#include "registers.hpp"
#include <vector>

class BaseMBC
{
	public:
		BaseMBC(uint8_t* romData, size_t romSize, uint8_t* ramData, size_t ramSize);

		virtual void write(KayosBoyPtr& address, uint8_t val) = 0;
		virtual void writeTwoBytes(KayosBoyPtr& address, uint16_t val) = 0;
		virtual uint8_t read(KayosBoyPtr& address) = 0;
		virtual uint16_t readTwoBytes(KayosBoyPtr& address) = 0;

	protected:
		std::vector<uint8_t> mStaticRomData; // This is Bank 0, or the always loaded bank;
		std::vector<uint8_t>* mRomBankData; // This is an array of vectors, each vector being a bank.
		std::vector<uint8_t>* mRamBankData; // This is an array of vectors, each vector being a bank.

};

class NoMBC : public BaseMBC
{
public:
	NoMBC(uint8_t* romData, size_t romSize, uint8_t* ramData, size_t ramSize);

	void write(KayosBoyPtr& address, uint8_t val);
	void writeTwoBytes(KayosBoyPtr& address, uint16_t val);
	uint8_t read(KayosBoyPtr& address);
	uint16_t readTwoBytes(KayosBoyPtr& address);

protected:

};

class MBC1 : public BaseMBC
{
public:
	MBC1(uint8_t* romData, size_t romSize, uint8_t* ramData, size_t ramSize);

	void write(KayosBoyPtr& address, uint8_t val);
	void writeTwoBytes(KayosBoyPtr& address, uint16_t val);
	uint8_t read(KayosBoyPtr& address);
	uint16_t readTwoBytes(KayosBoyPtr& address);

protected:

};

class MBC2 : public BaseMBC
{
public:
	MBC2(uint8_t* romData, size_t romSize, uint8_t* ramData, size_t ramSize);

	void write(KayosBoyPtr& address, uint8_t val);
	void writeTwoBytes(KayosBoyPtr& address, uint16_t val);
	uint8_t read(KayosBoyPtr& address);
	uint16_t readTwoBytes(KayosBoyPtr& address);

protected:

};

class MBC3 : public BaseMBC
{
public:
	MBC3(uint8_t* romData, size_t romSize, uint8_t* ramData, size_t ramSize);

	void write(KayosBoyPtr& address, uint8_t val);
	void writeTwoBytes(KayosBoyPtr& address, uint16_t val);
	uint8_t read(KayosBoyPtr& address);
	uint16_t readTwoBytes(KayosBoyPtr& address);

protected:

};

class MBC5 : public BaseMBC
{
public:
	MBC5(uint8_t* romData, size_t romSize, uint8_t* ramData, size_t ramSize);

	void write(KayosBoyPtr& address, uint8_t val);
	void writeTwoBytes(KayosBoyPtr& address, uint16_t val);
	uint8_t read(KayosBoyPtr& address);
	uint16_t readTwoBytes(KayosBoyPtr& address);

protected:

};

#endif // _MBC_H_