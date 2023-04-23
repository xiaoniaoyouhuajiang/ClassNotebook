#pragma once
#include "UnitFactory.h"
#include "HumanWithGun.h"
class HumanWithGunFactory :
	public UnitFactory
{
public:
	HumanWithGunFactory();
	~HumanWithGunFactory();
	std::shared_ptr<Unit> create(int x, int y, int level);
    std::string getPath();
};

