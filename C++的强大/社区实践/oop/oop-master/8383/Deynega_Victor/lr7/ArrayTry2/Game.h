#pragma once
#include "Rules.h"
#include "GameField.h"


class Game {
public:
	int turnCounter;
	int loser;
    Rule1* rule;
    Game();
    void startNewGame();
//	void play();
};


