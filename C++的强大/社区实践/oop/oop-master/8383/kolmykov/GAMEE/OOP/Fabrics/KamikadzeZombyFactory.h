#pragma once
#include "UnitFactory.h"
#include "KamikadzeZomby.h"
class KamikadzeZombyFactory :
	public UnitFactory
{
public:
	KamikadzeZombyFactory();
	~KamikadzeZombyFactory();
	std::shared_ptr<Unit> create(int x, int y, int level);
    std::string getPath();
};

