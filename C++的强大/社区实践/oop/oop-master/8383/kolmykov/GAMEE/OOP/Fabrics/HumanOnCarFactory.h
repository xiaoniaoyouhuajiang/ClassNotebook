#pragma once
#include "UnitFactory.h"
#include "HumanOnCar.h"
class HumanOnCarFactory :
	public UnitFactory
{
public:
	HumanOnCarFactory();
	~HumanOnCarFactory();
	std::shared_ptr<Unit> create(int x, int y, int level);
    std::string getPath();
};

