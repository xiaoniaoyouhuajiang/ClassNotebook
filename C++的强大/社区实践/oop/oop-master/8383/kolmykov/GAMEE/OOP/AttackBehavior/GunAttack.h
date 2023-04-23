#pragma once
#include "attackBehavior.h"
class GunAttack :
	public AttackBehavior
{
public:
	GunAttack();
	~GunAttack();
	void attack(std::shared_ptr<Unit> unit);
};

