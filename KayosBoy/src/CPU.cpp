#include "CPU.hpp"

CPU::CPU() :
	mRegisterAF(mRegisterA, mRegisterF),
	mRegisterBC(mRegisterB, mRegisterC),
	mRegisterDE(mRegisterD, mRegisterE),
	mRegisterHL(mRegisterH, mRegisterL)
{

}

