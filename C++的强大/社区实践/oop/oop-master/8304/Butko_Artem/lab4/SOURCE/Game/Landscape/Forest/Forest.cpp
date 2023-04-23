//
// Created by Artem Butko on 14/05/2020.
//

#include "Forest.h"

char Forest::getID()
{
    return this->id;
}

void Forest::getEffect(Object *object)
{
    if (object->id == 'S' || object->id == 'W') object->health.actHealed(50);
    else if (object->id == 'K' || object->id == 'C') object->damage.set(25, 5, 20);
    else object->health.actDamaged(25);
}
