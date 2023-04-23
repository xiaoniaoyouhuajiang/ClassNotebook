#pragma once
#include "UnitFactory.h"
#include "HumanOnBike.h"
class HumanOnBikeFactory :
	public UnitFactory
{
public:
	HumanOnBikeFactory();
	~HumanOnBikeFactory();
	std::shared_ptr<Unit> create(int x, int y, int level);
    std::string getPath();
};


