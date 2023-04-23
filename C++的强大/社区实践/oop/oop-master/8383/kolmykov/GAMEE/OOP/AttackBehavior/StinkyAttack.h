#pragma once
#include "attackBehavior.h"
class StinkyAttack :
	public AttackBehavior
{
public:
	StinkyAttack();
	~StinkyAttack();
	void attack(std::shared_ptr<Unit> unit);
};

