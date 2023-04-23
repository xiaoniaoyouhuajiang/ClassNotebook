#pragma once
#include <memory>
#include <vector>
#include "UnitBase.h"

struct RuleBase;
struct Player2;


struct PlayerBase
{
	PlayerBase(RuleBase* rule);

	size_t getNumber();


protected:
	RuleBase* rule;
	size_t number = 0;
};

struct Player1 : PlayerBase
{
	Player1(RuleBase* rule);
};

struct Player2 : PlayerBase
{
	Player2(RuleBase* rule);
};

struct Player3 : PlayerBase
{
	Player3(RuleBase* rule);
};