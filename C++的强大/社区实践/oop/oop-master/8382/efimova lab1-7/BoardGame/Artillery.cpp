#include "Artillery.h"

Artillery::ActionMeta Artillery::turnAction() {
	ActionMeta meta;
	return meta;
}

Cannon::Cannon() {
	_stats.health = 10;
	_stats.armor = 15;
	_stats.attack = 20;
}

Cannon::ActionMeta Cannon::userAction() {
	ActionMeta meta;
	return meta;
}

Cannon::ActionMeta Cannon::defend(Cannon::ActionMeta) {
	ActionMeta meta;
	return meta;
}

BoardUnit* Cannon::getCopy() {
	auto man = new Cannon();
	man->_stats = this->_stats;
	return man;
}

Catapult::Catapult() {
	_stats.health = 10;
	_stats.armor = 15;
	_stats.attack = 20;
}

Catapult::ActionMeta Catapult::userAction() {
	ActionMeta meta;
	return meta;
}

Catapult::ActionMeta Catapult::defend(Catapult::ActionMeta) {
	ActionMeta meta;
	return meta;
}

BoardUnit* Catapult::getCopy() {
	auto man = new Catapult();
	man->_stats = this->_stats;
	return man;
}

BoardUnit* ArtilleryFactory::getType(int type) {
	switch (type)
	{
	case 0:
		return (BoardUnit*)(new Cannon());
		break;
	case 1:
		return (BoardUnit*)(new Catapult());
		break;
	default:
		//throw
		return nullptr;
		break;
	}
}