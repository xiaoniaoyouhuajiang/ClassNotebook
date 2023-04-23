#pragma once
#include "UnitBase.h"

struct UnitTier1 : UnitBase
{
	
};

struct Mage : UnitTier1
{
	Mage();
	takeDamageResult takeDamage(size_t damageSize);
};

struct Assasin : UnitTier1
{
	Assasin();
	takeDamageResult takeDamage(size_t damageSize);
};