#include "HumanWithGunFactory.h"



HumanWithGunFactory::HumanWithGunFactory()
{
	type = UnitType::HUMAN_WITH_GUN;
    kind = Kind::HUMAN;
}


HumanWithGunFactory::~HumanWithGunFactory()
{
}

std::shared_ptr<Unit> HumanWithGunFactory::create(int x, int y, int level)
{
	return std::shared_ptr<Unit>(new HumanWithGun(x, y, level));
}


std::string HumanWithGunFactory::getPath() {
    return "humanWithGun.png";
}
