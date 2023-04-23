#pragma once
#include "MainUnitFactory.h"
#include "Horseman.h"
class HorsemanFactory : public MainUnitFactory {
public:
	Unit* createLvl1Unit();
	Unit* createLvl2Unit();
};

