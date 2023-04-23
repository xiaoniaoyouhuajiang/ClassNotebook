#include "Horseman.h"
#include "Field.h"
Horseman::Horseman() {
	this->setAttack(5);
	this->setHp(4);
	this->setArmor(1);
	this->setHaste(3);
	this->setRange(1);
	this->setUnitType(UnitTypes::HORSEMAN);
}
