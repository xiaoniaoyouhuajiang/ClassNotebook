#pragma once
#include "GameRules.h"
class GameRulesRandom : public GameRules
{
public:
	GameRulesRandom(Board* board);
	int changeTurn() override;
	int checkForEnd() override;
	void initBoard() override;
protected:
	Board* _board;
};

