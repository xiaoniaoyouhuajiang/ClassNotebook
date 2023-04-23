#include "UnitStatusMessage.h"



UnitStatusMessage::UnitStatusMessage()
{
}

UnitStatusMessage::UnitStatusMessage(std::shared_ptr<Unit> unit)
{
	this->unit = unit;
}


UnitStatusMessage::~UnitStatusMessage()
{
}

std::string UnitStatusMessage::toString()
{
	std::ostringstream os;
	//os << "Unit state: hp = " << unit->getHP() << " damage = " << unit->getLandDamage() + unit->getOwnDamage() + unit->getWeapon()->getDamage() << " armor " << unit->getArmor()->getDefend() + unit->getLandDefence() + unit->getOwnArmor() << "\n";
	os << unit;
	return os.str();
}
