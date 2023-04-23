//
// Created by Artem Butko on 19/05/2020.
//

#include "Potion.h"


Potion::Potion()
{
    this->id = '&';
    this->action = new ManaUp();
}

void Potion::getEffect(Object* unit)
{
    this->action->impact(unit);
}

void Potion::operator>>(Object *unit)
{
    getEffect(unit);
}
