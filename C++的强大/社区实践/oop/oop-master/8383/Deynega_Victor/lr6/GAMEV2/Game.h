#pragma once
#include "Rules.h"
#include "GameField.h"


template <class R> 
class Game {
	Game();
public:
	int turnCounter;
	int loser;
	R* rule;
	static Game* ptr;
	Game* getGame();
	void play();
};

Game<Rule1>* Game<Rule1>::ptr = nullptr;

Game<Rule2>* Game<Rule2>::ptr = nullptr;
