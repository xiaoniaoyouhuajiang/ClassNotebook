#include "Mediator.h"

void AttackMediator::attackBase(int attackPower, Base* base)
{
	base->downHP(attackPower);
}

void AttackMediator::attackUnit(int attackPower, IUnit* unit)
{
	if (unit->getArmour() <= attackPower)
	{
		attackPower -= unit->getArmour();
		unit->downArmour(unit->getArmour());
	}
	unit->downHP(attackPower);
}
