#include "StinkyZombyFactory.h"



StinkyZombyFactory::StinkyZombyFactory()
{
	type = UnitType::STINKY_ZOMBY;
    kind = Kind::ZOMBY;
}


StinkyZombyFactory::~StinkyZombyFactory()
{
}

std::shared_ptr<Unit> StinkyZombyFactory::create(int x, int y, int level)
{
	return std::shared_ptr<Unit>(new StinkyZomby(x, y, level));
}


std::string StinkyZombyFactory::getPath() {
    return "stinkyZomby.png";
}
