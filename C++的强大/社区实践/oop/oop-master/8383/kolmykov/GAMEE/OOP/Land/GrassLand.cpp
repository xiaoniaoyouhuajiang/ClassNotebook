#include "GrassLand.h"
#include "Unit.h"


GrassLand::GrassLand()
{
	type = LandType::GRASS_LAND;
}


GrassLand::~GrassLand()
{
}

void GrassLand::bufUnit(std::shared_ptr<Unit> unit)
{
	unit->setVisability(false);
	unit->setLandDamage(0);
	unit->setLandDefence(0);
}

char GrassLand::getChar()
{
	return '+';
}


std::string GrassLand::getPath() {
    return "grassLand.jpg";
}
