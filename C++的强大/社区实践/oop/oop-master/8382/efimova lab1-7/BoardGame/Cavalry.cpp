#include "Cavalry.h"

Cavalry::ActionMeta Cavalry::turnAction() {
	ActionMeta meta;
	return meta;
}

HeavyCavalry::HeavyCavalry() {
	_stats.health = 10;
	_stats.armor = 15;
	_stats.attack = 20;
}

HeavyCavalry::ActionMeta HeavyCavalry::userAction() {
	ActionMeta meta;
	return meta;
}

HeavyCavalry::ActionMeta HeavyCavalry::defend(HeavyCavalry::ActionMeta) {
	ActionMeta meta;
	return meta;
}

BoardUnit* HeavyCavalry::getCopy() {
	auto man = new HeavyCavalry();
	man->_stats = this->_stats;
	return man;
}

LightCavalry::LightCavalry() {
	_stats.health = 10;
	_stats.armor = 15;
	_stats.attack = 20;
}

LightCavalry::ActionMeta LightCavalry::userAction() {
	ActionMeta meta;
	return meta;
}

LightCavalry::ActionMeta LightCavalry::defend(LightCavalry::ActionMeta) {
	ActionMeta meta;
	return meta;
}

BoardUnit* LightCavalry::getCopy() {
	auto man = new LightCavalry();
	man->_stats = this->_stats;
	return man;
}

BoardUnit* CavalryFactory::getType(int type) {
	switch (type)
	{
	case 0:
		return (BoardUnit*)(new HeavyCavalry());
		break;
	case 1:
		return (BoardUnit*)(new LightCavalry());
		break;
	default:
		//throw
		return nullptr;
		break;
	}
}
