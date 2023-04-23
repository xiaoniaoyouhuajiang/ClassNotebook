#pragma once
#include "attackBehavior.h"
class AttackWithBat :
	public AttackBehavior
{
public:
	AttackWithBat();
	~AttackWithBat();
	void attack(std::shared_ptr<Unit> unit);
};

