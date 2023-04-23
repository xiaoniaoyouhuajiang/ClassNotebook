#pragma once
#include "GameRules.h"
#include "Board.h"
#include "User.h"
#include "PongoBaseBoardUnit.h"
class GameRulesClassic : public GameRules
{
public:
	GameRulesClassic(std::vector<User*> users, Board* board);
	int changeTurn() override;
	int checkForEnd() override;
	void initBoard() override;
protected:
	std::vector<User*> _users;
	Board* _board;
	int currentTurn = 0;
};

