#pragma once
#include "UnitFactory.h"
#include "BitingZomby.h"
class BitingZombyFactory :
	public UnitFactory
{
public:
	BitingZombyFactory();
	~BitingZombyFactory();
	std::shared_ptr<Unit> create(int x, int y, int level);
    std::string getPath();
};

