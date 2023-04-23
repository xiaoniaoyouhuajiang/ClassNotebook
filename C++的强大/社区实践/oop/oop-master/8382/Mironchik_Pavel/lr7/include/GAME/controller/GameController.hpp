#pragma once

#include <GAME/controller/PlayerState.hpp>

class GameBoard;

class GameController {
private:
	static GameController* _selectedController;
public:
	static void instance(GameController* instance) {
		_selectedController = instance;
	}

	static GameController* instance() {
		return _selectedController;
	}

	virtual GameBoard* board() = 0;
	virtual void newGame() = 0;
	virtual PlayerState& currentState() = 0;
	virtual void step() = 0;
	virtual bool isOver() = 0;
};