#pragma once
#include "UnitFactory.h"
#include "SpitToAreaZomby.h"
class SpitToAreaZombyFactory :
	public UnitFactory
{
public:
	SpitToAreaZombyFactory();
	~SpitToAreaZombyFactory();
	std::shared_ptr<Unit> create(int x, int y, int level);
    std::string getPath();
};

