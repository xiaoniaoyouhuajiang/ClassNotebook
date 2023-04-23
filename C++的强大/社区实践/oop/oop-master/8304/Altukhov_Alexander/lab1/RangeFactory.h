#pragma once
#include "MainUnitFactory.h"
#include "RangeUnit.h"
class RangeFactory : public MainUnitFactory {
public:
	Unit* createLvl1Unit();
	Unit* createLvl2Unit();
};

