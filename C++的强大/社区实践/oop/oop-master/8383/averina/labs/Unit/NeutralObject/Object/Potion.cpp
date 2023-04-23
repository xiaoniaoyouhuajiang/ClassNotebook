
#include "Potion.h"
#include "../Strategy/ManaUp.h"

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