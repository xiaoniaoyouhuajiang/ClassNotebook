#include "Nobjects.h"

HillingSatue::HillingSatue()
{
	name = 'H';
}

void HillingSatue::operator()(Unit* unit)
{
	strategy.get(20, unit);
}

ArmorStatue::ArmorStatue()
{
	name = 'A';
}

void ArmorStatue::operator()(Unit* unit)
{
	strategy.get(20, unit);
}

DamageStatue::DamageStatue()
{
	name = 'D';
}

void DamageStatue::operator()(Unit* unit)
{
	strategy.get(20, unit);
}

BigStatue::BigStatue()
{
	name = 'B';
}

void BigStatue::operator()(Unit* unit)
{
	strategy1.get(10, unit);
	strategy2.get(10, unit);
	strategy3.get(10, unit);
}

char Nobjects::getName()
{
	return name;
}
