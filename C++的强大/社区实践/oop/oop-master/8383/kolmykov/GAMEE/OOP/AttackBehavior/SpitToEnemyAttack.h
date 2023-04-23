#pragma once
#include "attackBehavior.h"
class SpitToEnemyAttack :
	public AttackBehavior
{
public:
	SpitToEnemyAttack();
	~SpitToEnemyAttack();
	void attack(std::shared_ptr<Unit> unit);
};

