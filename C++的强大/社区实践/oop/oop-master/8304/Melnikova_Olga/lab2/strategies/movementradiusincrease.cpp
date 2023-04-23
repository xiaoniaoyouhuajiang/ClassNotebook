#include "movementradiusincrease.h"


MovementRadiusIncrease::~MovementRadiusIncrease()
{

}

void MovementRadiusIncrease::interact(Unit *unit) {
    unit->movementRadius++;
}
