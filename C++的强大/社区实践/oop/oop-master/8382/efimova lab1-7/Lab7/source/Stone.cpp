#include "Stone.h"

std::string Stone::getName() {
	return "stone";
}

std::vector<Stone::ActionMeta> Stone::turnAction() {
	std::vector<Stone::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
}