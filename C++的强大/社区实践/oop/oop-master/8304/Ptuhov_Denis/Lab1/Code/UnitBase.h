#pragma once
#include <random>
#include "Resourses.h"

struct UnitBase
{
	virtual takeDamageResult takeDamage(size_t damageSize) = 0;
	void increaseDamage(size_t n);

	Damage damage;
	Hp hp;
	bool from_base = false;
	size_t range;
	size_t cost;
	char name;
};

