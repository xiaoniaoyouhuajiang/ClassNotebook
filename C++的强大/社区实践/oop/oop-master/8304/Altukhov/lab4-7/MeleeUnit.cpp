#include "MeleeUnit.h"



MeleeUnit::MeleeUnit() {

	// attack, hp, armor, haste, range, level, cost
	this->setAttack(1);
	this->setHp(2);
	this->setArmor(0);
	this->setHaste(1);
	this->setRange(1);
	this->setUnitType(UnitTypes::MELEE);
}
