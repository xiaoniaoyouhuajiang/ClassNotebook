#include "Stretegy.h"


void strategy_health::change_attribute(Unit *unit, int n) {
    unit->actHealed(n);
}

void strategy_armor::change_attribute(Unit *unit, int n) {
    unit->IncreaseArmor(n);
}

void strategy_dmg::change_attribute(Unit *unit, int n) {
    unit->IncreaseDmg(n);
}