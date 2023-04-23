
#include "Curse.h"
#include "../Strategy/Damn.h"

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