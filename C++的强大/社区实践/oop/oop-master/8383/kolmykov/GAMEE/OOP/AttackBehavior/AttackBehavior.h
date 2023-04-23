#pragma once
#include "AttackBehavior.h"
#include <memory>
#include "Weapon.h"
#include "Point.h"

class Unit;

class AttackBehavior {
public:
	AttackBehavior();
	virtual ~AttackBehavior();
	virtual void  attack(std::shared_ptr<Unit> unit);
};