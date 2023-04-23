#include "Tree.h"

std::string Tree::getName() {
	return "tree";
}

std::vector<Tree::ActionMeta> Tree::turnAction() {
	std::vector<Tree::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
}