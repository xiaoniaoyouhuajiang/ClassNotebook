#include "UnitTier1.h"

Mage::Mage()
{
	name = 'M';
	hp.increase(50);
	range = 5;
	damage.increase(10);
	cost = 3;
}

takeDamageResult Mage::takeDamage(size_t damageSize)
{
	if (damageSize >= hp.get())
		return takeDamageResult::death;

	hp.decrease(damageSize);
	return takeDamageResult::damageTaken;
}

Assasin::Assasin()
{
	name = 'X';
	hp.increase(150);
	damage.increase(10);
	cost = 3;
	range = 1;
}

takeDamageResult Assasin::takeDamage(size_t damageSize)
{
	if (damageSize >= hp.get())
		return takeDamageResult::death;

	size_t chance = std::rand() % 4;
	if (chance == 0)
		return takeDamageResult::dodge;

	hp.decrease(damageSize);
	return takeDamageResult::damageTaken;
}
