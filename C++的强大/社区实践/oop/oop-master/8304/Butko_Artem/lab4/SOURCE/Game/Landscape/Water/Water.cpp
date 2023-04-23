//
// Created by Artem Butko on 14/05/2020.
//

#include "Water.h"

char Water::getID()
{
    return this->id;
}

void Water::getEffect(Object *object)
{
    if (object->id =='W' || object->id == 'M') object->range.set(5);
    else object->health.actDamaged(250);
}
