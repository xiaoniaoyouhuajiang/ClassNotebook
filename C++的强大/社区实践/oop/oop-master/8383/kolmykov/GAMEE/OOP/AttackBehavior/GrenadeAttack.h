#pragma once
#include "attackBehavior.h"
class GrenadeAttack :
	public AttackBehavior
{
public:
	GrenadeAttack();
	~GrenadeAttack();
	void attack(std::shared_ptr<Unit> unit);
};

