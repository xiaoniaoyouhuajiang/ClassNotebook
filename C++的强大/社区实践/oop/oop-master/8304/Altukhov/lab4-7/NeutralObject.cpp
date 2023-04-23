#include "NeutralObject.h"
#include <iostream>
NeutralObjectTypes NeutralObject::getNeutralObjectType() {
	return type;
}

void NeutralObject::setNeutralObjectType(NeutralObjectTypes type) {
	this->type = type;
}

void NeutralObject::selectStrategy() {

	if (type == NeutralObjectTypes::TOWER) {
		strategy = new TowerStrategy;
	}
	else if (type == NeutralObjectTypes::WEAPONRY) {
		strategy = new WeaponryStrategy;
	}
	else if (type == NeutralObjectTypes::CANNON) {
		strategy = new CannonStrategy;
	}
	else if (type == NeutralObjectTypes::SHRINE) {
		strategy = new ShrineStrategy;
	}
}
void NeutralObject::applyEffect(Unit*& unit) {
	selectStrategy();
	//(*unit) << strategy;
	strategy->applyEffect(unit);


}

void NeutralObject::removeEffect(Unit*& unit) {
	selectStrategy();
	strategy->removeEffect(unit);
}

void operator<<(Unit& unit, Strategy* strategy) {

	strategy->applyEffectForTimur(unit);

}

