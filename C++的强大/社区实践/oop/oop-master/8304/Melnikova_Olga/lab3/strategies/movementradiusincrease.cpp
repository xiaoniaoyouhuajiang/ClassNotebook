#include "movementradiusincrease.h"


MovementRadiusIncrease::~MovementRadiusIncrease()
{

}

void MovementRadiusIncrease::interact(Unit *unit) { //пример
    unit->movementRadius++;
}
