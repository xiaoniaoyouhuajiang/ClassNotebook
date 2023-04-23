#include "UnitTier2.h"

Archer::Archer()
{
	name = 'A';
	hp.increase(50);
	range = 5;
	damage.increase(10);
	cost = 3;
}

takeDamageResult Archer::takeDamage(size_t damageSize)
{
	if (damageSize >= hp.get())
		return takeDamageResult::death;

	hp.decrease(damageSize);
	return takeDamageResult::damageTaken;
}

Spearman::Spearman()
{
	name = 'R';
	hp.increase(150);
	damage.increase(10);
	cost = 3;
	range = 1;
}

takeDamageResult Spearman::takeDamage(size_t damageSize)
{
	if (damageSize >= hp.get())
		return takeDamageResult::death;

	hp.decrease(damageSize);
	return takeDamageResult::damageTaken;
}
