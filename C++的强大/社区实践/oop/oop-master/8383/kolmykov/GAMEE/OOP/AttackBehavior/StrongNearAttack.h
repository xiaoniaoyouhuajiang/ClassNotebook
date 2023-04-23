#pragma once
#include "attackBehavior.h"
class StrongNearAttack :
	public AttackBehavior
{
public:
	StrongNearAttack();
	~StrongNearAttack();
	void attack(std::shared_ptr<Unit> unit);
};

