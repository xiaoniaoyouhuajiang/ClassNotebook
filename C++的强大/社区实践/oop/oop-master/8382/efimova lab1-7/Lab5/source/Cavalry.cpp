#include "Cavalry.h"
#include "PongoBoardUnit.h"
#include "PongoBaseBoardUnit.h"
#include "Game.h"
#include <QDebug>

Cavalry::Cavalry(PongoBaseBoardUnit* base) : PongoBoardUnit(base) {

}

std::string Cavalry::getClassName() {
	return "cavalry";
}

std::vector<Cavalry::ActionMeta> Cavalry::turnAction() {
	std::vector<Cavalry::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
}

HeavyCavalry::HeavyCavalry(PongoBaseBoardUnit* base) : Cavalry(base) {
	_stats.health = 30;
	_stats.armor = 15;
	_stats.attack = 20;
}

std::vector<HeavyCavalry::ActionMeta> HeavyCavalry::userAction(Board::BoardCell targetCell, int action) {
	std::vector<HeavyCavalry::ActionMeta> actionVec;
	ActionMeta meta;
	meta.fromUnit = this;
	if (targetCell.isEmpty && targetCell.terrainUnit->isPassable()) {
		meta.isEmpty = false;
		meta.isMove = true;
		meta.moveX = targetCell.x;
		meta.moveY = targetCell.y;
	}
	else if (!targetCell.isEmpty) {
		auto targetUnit = dynamic_cast<PongoBoardUnit*>(targetCell.unit);
		if (targetUnit != nullptr) {
			meta.isEmpty = false;
			meta.toUnit = targetCell.unit;
			meta.isAttack = true;
			meta.hpAttack = _stats.attack;
			meta.armorAttack = (int)_stats.attack/3;
		}
	}
	actionVec.push_back(meta);
	return actionVec;
	actionVec.push_back(meta);
	return actionVec;
}

std::vector<HeavyCavalry::ActionMeta> HeavyCavalry::defend(HeavyCavalry::ActionMeta meta) {
	if (meta.isAttack) {
		_stats.health -= meta.hpAttack;
		if (_stats.health <= 0) {
			_base->unitDeathHook(this);
		}
		_stats.armor -= meta.armorAttack;
		if (_stats.armor <= 0)
			_stats.armor = 0;
	}
	std::vector<HeavyCavalry::ActionMeta> actionVec;
	ActionMeta defendMeta;
	actionVec.push_back(defendMeta);
	return actionVec;
}

std::string HeavyCavalry::getName() {
	return "heavy_cavalry";
}

LightCavalry::LightCavalry(PongoBaseBoardUnit* base) : Cavalry(base) {
	_stats.health = 10;
	_stats.armor = 15;
	_stats.attack = 20;
}

std::vector<LightCavalry::ActionMeta> LightCavalry::userAction(Board::BoardCell targetCell, int action) {
	std::vector<LightCavalry::ActionMeta> actionVec;
	ActionMeta meta;
	if (targetCell.isEmpty && targetCell.terrainUnit->isPassable()) {
		meta.isMove = true;
		meta.moveX = targetCell.x;
		meta.moveY = targetCell.y;
	}
	actionVec.push_back(meta);
	return actionVec;
}

std::vector<LightCavalry::ActionMeta> LightCavalry::defend(LightCavalry::ActionMeta) {
	std::vector<LightCavalry::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
}

std::string LightCavalry::getName() {
	return "light_cavalry";
}

PlayableBoardUnit* CavalryFactory::createUnit(int type) {
	switch (type)
	{
	case 0:
		return (PlayableBoardUnit*)(new HeavyCavalry(_base));
		break;
	case 1:
		return (PlayableBoardUnit*)(new LightCavalry(_base));
		break;
	default:
		//throw
		return nullptr;
		break;
	}
}

PlayableBoardUnit* CavalryFactory::createUnit(QJsonObject snapshot) {
	auto type = snapshot["subtype"].toString();
	if (type == "heavy_cavalry") {
		auto unit = (PlayableBoardUnit*)(new HeavyCavalry(snapshot, _base));
		return unit;
	}
	else if (type == "light_cavalry")
		return (PlayableBoardUnit*)(new LightCavalry(snapshot, _base));
	else
		return nullptr;
}