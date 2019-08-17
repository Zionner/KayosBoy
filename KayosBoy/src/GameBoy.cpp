#include "GameBoy.hpp"

GameBoy::GameBoy(Cartridge& cartToLoad) :
	mCycleCount(0),
	mCartridge(cartToLoad)
{

}