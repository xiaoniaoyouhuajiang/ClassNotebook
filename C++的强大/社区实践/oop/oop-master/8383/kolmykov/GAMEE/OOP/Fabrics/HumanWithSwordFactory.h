#pragma once
#include "UnitFactory.h"
#include "HumanWithSword.h"
class HumanWithSwordFactory :
	public UnitFactory
{
public:
	HumanWithSwordFactory();
	~HumanWithSwordFactory();
	std::shared_ptr<Unit> create(int x, int y, int level);
    std::string getPath();
};

