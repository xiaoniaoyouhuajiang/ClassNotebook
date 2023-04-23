#pragma once
#include "UnitFactory.h"
#include "StinkyZomby.h"
class StinkyZombyFactory :
	public UnitFactory
{
public:
	StinkyZombyFactory();
	~StinkyZombyFactory();
	std::shared_ptr<Unit> create(int x, int y, int level);
    std::string getPath();
};

