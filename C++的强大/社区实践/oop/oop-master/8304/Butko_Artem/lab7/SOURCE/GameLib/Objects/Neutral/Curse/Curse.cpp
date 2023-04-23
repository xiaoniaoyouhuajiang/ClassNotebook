//
// Created by Artem Butko on 19/05/2020.
//

#include "Curse.h"

Curse::Curse()
{
    this->id = '$';
    this->action = new Damn();
}

void Curse::getEffect(Object* unit)
{
    this->action->impact(unit);
}

void Curse::operator>>(Object *unit)
{
    getEffect(unit);
}
