#include "RangeUnit.h"

RangeUnit::RangeUnit() {
	// attack, hp, armor, haste, range, level, cost
	this->setAttack(3);
	this->setHp(3);
	this->setArmor(0);
	this->setHaste(2);
	this->setRange(4);
	this->setUnitType(UnitTypes::RANGE);
}
