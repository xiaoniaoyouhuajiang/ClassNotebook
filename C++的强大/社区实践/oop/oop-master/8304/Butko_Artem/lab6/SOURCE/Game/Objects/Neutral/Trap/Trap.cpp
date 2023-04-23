//
// Created by Artem Butko on 19/05/2020.
//

#include "Trap.h"

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
