#pragma once
#include "UnitFactory.h"
#include "HumanWithBat.h"
class HumanWithBatFactory :
	public UnitFactory
{
public:
	HumanWithBatFactory();
	~HumanWithBatFactory();
	std::shared_ptr<Unit> create(int x, int y, int level);
    std::string getPath();
};

