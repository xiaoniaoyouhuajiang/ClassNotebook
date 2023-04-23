#include "SpitToAreaZombyFactory.h"



SpitToAreaZombyFactory::SpitToAreaZombyFactory()
{
	type = UnitType::SPIT_TO_AREA_ZOMBY;
    kind = Kind::ZOMBY;
}


SpitToAreaZombyFactory::~SpitToAreaZombyFactory()
{
}

std::shared_ptr<Unit> SpitToAreaZombyFactory::create(int x, int y, int level)
{
	return std::shared_ptr<Unit>(new SpitToAreaZomby(x, y, level));
}


std::string SpitToAreaZombyFactory::getPath() {
    return "spitToAreaZomby.png";
}
