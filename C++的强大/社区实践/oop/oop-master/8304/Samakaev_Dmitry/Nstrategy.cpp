#include "Nstrategy.h"

void HillingStrategy::get(int n, Unit* unit)
{
	unit->hp.change(unit->hp.get() + n);
}

void ArmorStrategy::get(int n, Unit* unit)
{
	unit->armor.change(unit->armor.get() + n);
}

void DamageStrategy::get(int n, Unit* unit)
{
	unit->damage.change(unit->damage.get() + n);
}
