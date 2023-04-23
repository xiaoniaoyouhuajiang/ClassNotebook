#include "attackradiusincrease.h"


AttackRadiusIncrease::~AttackRadiusIncrease()
{

}

void AttackRadiusIncrease::interact(Unit *unit) {
    unit->attackRadius++;
    unit->AttackRadiusBetter++;
}
