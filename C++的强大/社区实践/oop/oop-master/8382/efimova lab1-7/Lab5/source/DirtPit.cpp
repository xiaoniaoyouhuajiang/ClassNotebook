#include "DirtPit.h"

std::string DirtPit::getName() {
	return "dirt_pit";
}

std::vector<DirtPit::ActionMeta> DirtPit::turnAction() {
	std::vector<DirtPit::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
}