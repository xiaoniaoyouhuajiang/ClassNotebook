#pragma once
#include "MainUnitFactory.h"
#include "MeleeUnit.h"
class MeleeFactory : public MainUnitFactory {
public:
	Unit* createLvl1Unit();
	Unit* createLvl2Unit();
};

