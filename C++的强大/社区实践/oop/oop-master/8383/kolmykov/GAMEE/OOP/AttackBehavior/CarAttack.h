#pragma once
#include "attackBehavior.h"
class CarAttack :
	public AttackBehavior
{
public:
	CarAttack();
	~CarAttack();
	void attack(std::shared_ptr<Unit> unit);
};

