//
// Created by Artem Butko on 14/05/2020.
//

#include "Mountain.h"

char Mountain::getID()
{
    return this->id;
}

void Mountain::getEffect(Object *object)
{
    if (object->id == 'M' || object->id == 'C') object->damage.set(40, 3, 50);
    else if (object->id == 'A' || object->id == 'K') object->mana.actRecovered(50);
    else object->health.actDamaged(40);
}
