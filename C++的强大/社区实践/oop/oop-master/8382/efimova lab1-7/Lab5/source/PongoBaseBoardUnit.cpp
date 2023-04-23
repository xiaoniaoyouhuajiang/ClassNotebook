#include "PongoBaseBoardUnit.h"
#include "Artillery.h"
#include "Cavalry.h"
#include "Infantry.h"
#include "Game.h"
#include <QDebug>

PongoBaseBoardUnit::PongoBaseBoardUnit() {
	auto artilleryFactory = new ArtilleryFactory(this);
	auto cavalryFactory = new CavalryFactory(this);
	auto infantryFactory = new InfantryFactory(this);
	factories.insert(std::pair<std::string, BoardUnitFactory*>("artillery", artilleryFactory));
	factories.insert(std::pair<std::string, BoardUnitFactory*>("infantry", infantryFactory));
	factories.insert(std::pair<std::string, BoardUnitFactory*>("cavalry", cavalryFactory));
}

PongoBaseBoardUnit::BaseStats PongoBaseBoardUnit::getBaseStats() {
	return _baseStats;
}

std::vector<PongoBaseBoardUnit::ActionMeta> PongoBaseBoardUnit::userAction(Board::BoardCell targetCell, int action) {
	std::vector<PongoBaseBoardUnit::ActionMeta> actionVec;
	ActionMeta meta;
	if (targetCell.isEmpty) {
		meta.isEmpty = false;
		meta.fromUnit = this;
		meta.isCreate = true;
		auto newUnit = factories.at("cavalry")->createUnit();
		meta.createdUnit = newUnit;
		auto coords = Game::getInstance()->getBoard()->getUnitCoords(targetCell.terrainUnit);
		meta.unitX = coords.first;
		meta.unitY = coords.second;
	}
	actionVec.push_back(meta);
	_baseStats.unitCount++;
	return actionVec;
	//unit creation
}

std::vector<PongoBaseBoardUnit::ActionMeta> PongoBaseBoardUnit::defend(PongoBaseBoardUnit::ActionMeta) {
	std::vector<PongoBaseBoardUnit::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
	//unit creation
}

std::vector<PongoBaseBoardUnit::ActionMeta> PongoBaseBoardUnit::turnAction() {
	std::vector<PongoBaseBoardUnit::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
	//unit creation
}

std::string PongoBaseBoardUnit::getName() {
	return "base";
}

void PongoBaseBoardUnit::unitDeathHook(BoardUnit* dyingUnit) {
	qInfo() << "Deleting unit, id:" << dyingUnit->getID();
	Game::getInstance()->getBoard()->removeUnit(dyingUnit);
	delete dyingUnit;
	_baseStats.unitCount--;
}

QJsonObject PongoBaseBoardUnit::getSnapshot() {
	QJsonObject baseUnitSnapshot;

	QJsonObject baseStats;

	baseStats.insert("health", _stats.health);
	baseStats.insert("level", _baseStats.level);
	baseStats.insert("maxUnitCreationPerTurn", _baseStats.maxUnitCreationPerTurn);
	baseStats.insert("maxUnit", _baseStats.maxUnit);
	baseStats.insert("unitCount", _baseStats.unitCount);

	baseUnitSnapshot.insert("baseStats", baseStats);

	QJsonArray units;
	baseUnitSnapshot.insert("units", units);
	baseUnitSnapshot.insert("type", "base");
	return baseUnitSnapshot;
}

PongoBaseBoardUnit::PongoBaseBoardUnit(QJsonObject snapshot, Board* board) {
	auto artilleryFactory = new ArtilleryFactory(this);
	auto cavalryFactory = new CavalryFactory(this);
	auto infantryFactory = new InfantryFactory(this);
	factories.insert(std::pair<std::string, BoardUnitFactory*>("artillery", artilleryFactory));
	factories.insert(std::pair<std::string, BoardUnitFactory*>("infantry", infantryFactory));
	factories.insert(std::pair<std::string, BoardUnitFactory*>("cavalry", cavalryFactory));

	auto baseStats = snapshot["baseStats"].toObject();
	_stats.health = baseStats["health"].toInt();
	_baseStats.level = baseStats["level"].toInt();
	_baseStats.maxUnit = baseStats["maxUnit"].toInt();
	_baseStats.maxUnitCreationPerTurn = baseStats["maxUnitCreationPerTurn"].toInt();
	_baseStats.unitCount = baseStats["unitCount"].toInt();

	auto unitArray = snapshot["units"].toArray();

	for (int i = 0; i < unitArray.size(); i++) {
		auto unitSnapshot = unitArray[i].toObject();
		auto _class = unitSnapshot["class"].toString();

		auto unit = factories.at(_class.toStdString())->createUnit(unitSnapshot);
		board->addUnit(unit, unitSnapshot["x"].toInt(), unitSnapshot["y"].toInt());
	}
}