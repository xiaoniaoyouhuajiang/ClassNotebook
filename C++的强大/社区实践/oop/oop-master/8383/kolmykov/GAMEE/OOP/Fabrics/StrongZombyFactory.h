#pragma once
#include "UnitFactory.h"
#include "StrongZomby.h"
class StrongZombyFactory :
	public UnitFactory
{
public:
	StrongZombyFactory();
	~StrongZombyFactory();
	std::shared_ptr<Unit> create(int x, int y, int level);
    std::string getPath();
};

