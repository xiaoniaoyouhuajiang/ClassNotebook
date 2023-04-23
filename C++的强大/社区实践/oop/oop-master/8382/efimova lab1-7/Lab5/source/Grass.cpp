#include "Grass.h"

bool Grass::isPassable() {
	return true;
}

std::vector<Grass::ActionMeta> Grass::turnAction() {
	std::vector<Grass::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
}

std::string Grass::getName() {
	return "grass";
}
