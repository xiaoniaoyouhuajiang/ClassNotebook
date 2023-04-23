#include "UnitTier3.h"

Scout::Scout()
{
	name = 'S';
	hp.increase(50);
	range = 5;
	damage.increase(40);
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
	damage.increase(40);
	cost = 3;
	range = 1;
}

takeDamageResult Warrior::takeDamage(size_t damageSize)
{
	if (damageSize >= hp.get())
		return takeDamageResult::death;

	size_t chance = std::rand() % 5;
	if (chance == 0)
		return takeDamageResult::block;

	hp.decrease(damageSize);
	return takeDamageResult::damageTaken;
}
