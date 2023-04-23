#include "UnitTier3.h"

Scout::Scout()
{
	name = 'S';
	hp.increase(50);
	range = 5;
	damage.increase(10);
	cost = 3;
}

takeDamageResult Scout::takeDamage(size_t damageSize)
{
	if (damageSize >= hp.get())
		return takeDamageResult::death;

	hp.decrease(damageSize);
	return takeDamageResult::damageTaken;
}

Warrior::Warrior()
{
	name = 'W';
	hp.increase(150);
	damage.increase(10);
	cost = 3;
	range = 1;
}

takeDamageResult Warrior::takeDamage(size_t damageSize)
{
	if (damageSize >= hp.get())
		return takeDamageResult::death;

	hp.decrease(damageSize);
	return takeDamageResult::damageTaken;
}
