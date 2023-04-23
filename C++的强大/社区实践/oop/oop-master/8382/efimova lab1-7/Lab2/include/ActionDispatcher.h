#pragma once
#include "Board.h"
#include <queue>
class ActionDispatcher
{
public:	//спрашиваем юниты, что они хотят сделать и делают это
	ActionDispatcher(Board* board);
	void push_back(BoardUnit::ActionMeta meta);
	void flush();	//сливаем наш буфер
	void exec(BoardUnit::ActionMeta meta);	//загруж. в память вместо старого
protected:

	Board* mBoard = nullptr;
};

