#pragma once
#include "UnitBase.h"

struct UnitTier2 : UnitBase
{

};

struct Archer : UnitTier2
{
	Archer();
	takeDamageResult takeDamage(size_t damageSize);
};

struct Spearman : UnitTier2
{
	Spearman();
	takeDamageResult takeDamage(size_t damageSize);
};