#pragma once
#include "AttackBehavior.h"

class BikeAttack :
	public AttackBehavior
{
public:
	BikeAttack();
	~BikeAttack();
	void attack(std::shared_ptr<Unit> unit);
};

