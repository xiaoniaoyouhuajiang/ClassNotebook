#pragma once
#include "IUnit.h"
#include "Base.h"

class Mediator
{
public:
	virtual void attackBase(int attackPower, Base* base) = 0;
	virtual void attackUnit(int attackPower, IUnit* unit) = 0;
};

class AttackMediator : public Mediator
{
public:
	AttackMediator() {};
	void attackBase(int attackPower, Base* base) override;
	void attackUnit(int attackPower, IUnit* unit) override;
};