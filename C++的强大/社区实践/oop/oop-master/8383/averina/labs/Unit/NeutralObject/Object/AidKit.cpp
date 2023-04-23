
#include "AidKit.h"
#include "../Refresh.h"

AidKit::AidKit()
{
    this->id = '+';
    this->action = new Refresh();
}

void AidKit::getEffect(Object* unit)
{
    this->action->impact(unit);
}

void AidKit::operator>>(Object *unit)
{
    getEffect(unit);
}