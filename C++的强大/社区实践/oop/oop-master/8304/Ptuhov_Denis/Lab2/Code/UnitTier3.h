#pragma once
#include "UnitBase.h"

struct UnitTier3 : UnitBase
{

};

struct Scout : UnitTier3
{
	Scout();
	takeDamageResult takeDamage(size_t damageSize);
};

struct Warrior : UnitTier3
{
	Warrior();
	takeDamageResult takeDamage(size_t damageSize);
};