#pragma once
#include "Board.h"
#include <queue>
class ActionDispatcher
{
public:
	struct Action {
		std::pair<int, int> fromCell;
		std::pair<int, int> toCell;
		std::string actionType;
	};
	ActionDispatcher(Board* board);
	void push_back(BoardUnit::ActionMeta meta);
	std::vector<Action>* flush();
	void ImmediateExec(BoardUnit::ActionMeta meta);
protected:
	std::queue<BoardUnit::ActionMeta> actionQueue;
	Board* mBoard = nullptr;
};

