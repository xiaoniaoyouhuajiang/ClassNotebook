#pragma once
#include "UnitFactory.h"
#include "SpitToEnemyZomby.h"
class SpitToEnemyZombyFactory :
	public UnitFactory
{
public:
	SpitToEnemyZombyFactory();
	~SpitToEnemyZombyFactory();
	std::shared_ptr<Unit> create(int x, int y, int level);
    std::string getPath();
};

