#include "CommonLand.h"
#include "Unit.h"


CommonLand::CommonLand()
{
	type = LandType::COMMON_LAND;
}


CommonLand::~CommonLand()
{
}

void CommonLand::bufUnit(std::shared_ptr<Unit> unit) {
	unit->setVisability(true);
	unit->setLandDamage(0);
	unit->setLandDefence(0);
}

char CommonLand::getChar()
{
	return ' ';
}


std::string CommonLand::getPath() {
    return "commonLand.jpg";
}
