#pragma once
#include <vector>
#include "GameRules.h"
#include "User.h"
// шблон принимает 4 параметра: 1 - массив игроков, 2 - указатель на доску, 3 - тип, 4 - тип, 5 - доп. параметр
template <std::vector<User*>* users, Board* board, int turnChangeType, int endCriteriaType, std::vector<int>* boardInitArgs>
class GameRulesCustom : public GameRules
{
public:
	GameRulesCustom();
	int changeTurn() override; // переопред. в дочернем вирт. ф-цию
	int checkForEnd() override;
	void initBoard() override;
protected:
	int currentTurn = 0; // обнуляем для работы в дальнейшем
};

