#include "UnitBase.h"

void Hp::decrease(size_t n)
{
	hp -= n;
}

void Hp::increase(size_t n)
{
	hp += n;
}

size_t Hp::get()
{
	return hp;
}

void Damage::decrease(size_t n)
{
	damage += n;
}

void Damage::increase(size_t n)
{
	damage += n;
}

size_t Damage::get()
{
	return damage;
}

void UnitBase::increaseDamage(size_t n)
{
	damage.increase(n);
}
