#pragma once

#include <GAME/controller/PlayerState.hpp>

class GameBoard;

template<int playersCount>
class Rules {
public:
	virtual GameBoard* makeBoard() = 0;
	virtual PlayerState& currentState() = 0;
	virtual void step(GameBoard* board) = 0;
	virtual bool isOver(GameBoard* board) = 0;
};