#pragma once
#include "attackBehavior.h"
class SpitToAreaAttack :
	public AttackBehavior
{
public:
	SpitToAreaAttack();
	~SpitToAreaAttack();
	void attack(std::shared_ptr<Unit> unit);
};

