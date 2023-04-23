#include "TreeLog.h"

std::string TreeLog::getName() {
	return "tree_log";
}

std::vector<TreeLog::ActionMeta> TreeLog::turnAction() {
	std::vector<TreeLog::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
}