#pragma once
#include "AttackBehavior.h"
class SwordAttack :
	public AttackBehavior
{
public:
	SwordAttack();
	~SwordAttack();
	void attack(std::shared_ptr<Unit> unit);
};

