#include "Trap.h"
#include "../Strategy/HelthDown.h"

Trap::Trap()
{
    this->id = '*';
    this->action = new HealthDown();
}

void Trap::getEffect(Object *unit)
{
    this->action->impact(unit);
}

void Trap::operator>>(Object *unit)
{
    getEffect(unit);
}