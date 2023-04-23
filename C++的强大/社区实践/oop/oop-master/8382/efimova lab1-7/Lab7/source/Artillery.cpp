#include "Artillery.h"

Artillery::Artillery(PongoBaseBoardUnit* base) : PongoBoardUnit(base) {

}

std::string Artillery::getClassName() {
	return "artillery";
}

std::vector<Artillery::ActionMeta> Artillery::turnAction() {
	std::vector<Cannon::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
}

Cannon::Cannon(PongoBaseBoardUnit* base) : Artillery(base) {
	_stats.health = 10;
	_stats.armor = 15;
	_stats.attack = 20;
}

std::vector<Cannon::ActionMeta> Cannon::userAction(Board::BoardCell targetCell, int action) {
	std::vector<Cannon::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
}

std::vector<Cannon::ActionMeta> Cannon::defend(Cannon::ActionMeta) {
	std::vector<Cannon::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
}

std::string Cannon::getName() {
	return "cannon";
}

Catapult::Catapult(PongoBaseBoardUnit* base) : Artillery(base) {
	_stats.health = 10;
	_stats.armor = 15;
	_stats.attack = 20;
}

std::vector<Cannon::ActionMeta> Catapult::userAction(Board::BoardCell targetCell, int action) {
	std::vector<Cannon::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
}

std::vector<Cannon::ActionMeta> Catapult::defend(Catapult::ActionMeta) {
	std::vector<Cannon::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
}

std::string Catapult::getName() {
	return "catapult";
}

PlayableBoardUnit* ArtilleryFactory::createUnit(int type) {
	switch (type)
	{
	case 0:
		return (PlayableBoardUnit*)(new Cannon(_base));
		break;
	case 1:
		return (PlayableBoardUnit*)(new Catapult(_base));
		break;
	default:
		//throw
		return nullptr;
		break;
	}
}

PlayableBoardUnit* ArtilleryFactory::createUnit(QJsonObject snapshot) {
	auto type = snapshot["subtype"];
	if (type == "cannon")
		return (PlayableBoardUnit*)(new Cannon(snapshot, _base));
	else if (type == "catapult")
		return (PlayableBoardUnit*)(new Catapult(snapshot, _base));
	else
		return nullptr;
}