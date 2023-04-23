
#include "Puddle.h"

char Puddle::getID()
{
    return this->id;
}

void Puddle::getEffect(Object *object)
{
    if (object->id =='W' || object->id == 'M') object->range.set(5);
    else object->health.actDamaged(250);
}