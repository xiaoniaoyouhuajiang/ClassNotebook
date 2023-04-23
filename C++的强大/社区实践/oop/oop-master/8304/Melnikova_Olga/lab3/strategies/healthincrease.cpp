#include "healthincrease.h"


HealthIncrease::~HealthIncrease()
{

}

void HealthIncrease::interact(Unit *unit) {
    unit->health++;
}
