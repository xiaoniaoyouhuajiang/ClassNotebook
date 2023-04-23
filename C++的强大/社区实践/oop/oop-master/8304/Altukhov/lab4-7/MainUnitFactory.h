#pragma once
#include "Unit.h"
class MainUnitFactory {

public:
	virtual Unit* createLvl1Unit() = 0;
	virtual Unit* createLvl2Unit() = 0;
};

