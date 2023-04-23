#pragma once
#include "UnitFactory.h"
#include "HumanWithGrenade.h"
class HumanWithGrenadeFactory :
	public UnitFactory
{
public:
	HumanWithGrenadeFactory();
	~HumanWithGrenadeFactory();
	std::shared_ptr<Unit> create(int x, int y, int level);
    std::string getPath();
};

