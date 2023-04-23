#pragma once
#include "Board.h"
class GameRules	//отец
{
public:
	virtual int changeTurn() = 0;	//измениь ход
	virtual int checkForEnd() = 0;	//проверка на проигрыш или выйгрыш
	virtual void initBoard() = 0;	//иниц. доску
protected:
	GameRules();
};
//std::vector<User> доб. как аргумент
