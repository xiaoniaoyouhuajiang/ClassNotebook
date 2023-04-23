#include "KamikadzeZombyFactory.h"



KamikadzeZombyFactory::KamikadzeZombyFactory()
{
	type = UnitType::KAMIKADZE_ZOMBY;
    kind = Kind::ZOMBY;
}


KamikadzeZombyFactory::~KamikadzeZombyFactory()
{
}

std::shared_ptr<Unit> KamikadzeZombyFactory::create(int x, int y, int level)
{
	return std::shared_ptr<Unit>(new KamikadzeZomby(x, y, level));
}


std::string KamikadzeZombyFactory::getPath() {
    return "kamikadzeZomby.png";
}
