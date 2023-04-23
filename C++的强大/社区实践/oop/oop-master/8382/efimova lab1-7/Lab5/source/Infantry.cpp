#include "Infantry.h"

Infantry::Infantry(PongoBaseBoardUnit* base) : PongoBoardUnit(base) {

}

std::string Infantry::getClassName() {
	return "infantry";
}

std::vector<Infantry::ActionMeta> Infantry::turnAction() {
	std::vector<Infantry::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
}

Swordsman::Swordsman(PongoBaseBoardUnit* base) : Infantry(base) {
	_stats.health = 10;
	_stats.armor = 15;
	_stats.attack = 20;
}

std::vector<Swordsman::ActionMeta> Swordsman::userAction(Board::BoardCell targetCell, int action) {
	std::vector<Swordsman::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
}

std::vector<Swordsman::ActionMeta> Swordsman::defend(Swordsman::ActionMeta) {
	std::vector<Swordsman::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
}

std::string Swordsman::getName() {
	return "swordsman";
}

Spearman::Spearman(PongoBaseBoardUnit* base) : Infantry(base) {
	_stats.health = 10;
	_stats.armor = 15;
	_stats.attack = 20;
}

std::vector<Spearman::ActionMeta> Spearman::userAction(Board::BoardCell targetCell, int action) {
	std::vector<Spearman::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
}

std::vector<Spearman::ActionMeta> Spearman::defend(Spearman::ActionMeta) {
	std::vector<Spearman::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
}

std::string Spearman::getName() {
	return "spearman";
}

PlayableBoardUnit* InfantryFactory::createUnit(int type) {
	switch (type)
	{
	case 0:
		return (PlayableBoardUnit*)(new Swordsman(_base));
		break;
	case 1:
		return (PlayableBoardUnit*)(new Spearman(_base));
		break;
	default:
		//throw
		return nullptr;
		break;
	}
}

PlayableBoardUnit* InfantryFactory::createUnit(QJsonObject snapshot) {
	auto type = snapshot["subtype"];
	if (type == "spearman")
		return (PlayableBoardUnit*)(new Spearman(snapshot, _base));
	else if (type == "swordsman")
		return (PlayableBoardUnit*)(new Swordsman(snapshot, _base));
	else
		return nullptr;
}

