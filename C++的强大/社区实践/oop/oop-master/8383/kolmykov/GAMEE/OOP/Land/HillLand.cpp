#include "HillLand.h"
#include "Unit.h"


HillLand::HillLand()
{
	type = LandType::HILL_LAND;
}


HillLand::~HillLand()
{
}

void HillLand::bufUnit(std::shared_ptr<Unit> unit) {
	unit->setVisability(true);
	unit->setLandDamage(50);
	unit->setLandDefence(50);
}

char HillLand::getChar()
{
	return '^';
}


std::string HillLand::getPath() {
    return "hillLand.jpg";
}
