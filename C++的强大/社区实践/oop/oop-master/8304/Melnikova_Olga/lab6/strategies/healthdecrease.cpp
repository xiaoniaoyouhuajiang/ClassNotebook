#include "healthdecrease.h"


HealthDecrease::~HealthDecrease()
{

}

void HealthDecrease::interact(Unit *unit) {
    if (unit->health > 1) unit->health--;
}
