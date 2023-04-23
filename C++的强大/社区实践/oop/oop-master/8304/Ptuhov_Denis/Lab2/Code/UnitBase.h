#pragma once
#include <random>
#include <memory>
#include "Resourses.h"
#include "NtrkObj.h"

struct UnitBase
{
	virtual takeDamageResult takeDamage(size_t damageSize) = 0;
	void increaseDamage(size_t n);
	void operator()(std::shared_ptr<NtrlObj> ntrl);

	Damage damage;
	Hp hp;
	bool from_base = false;
	size_t range;
	size_t cost;
	char name;
};