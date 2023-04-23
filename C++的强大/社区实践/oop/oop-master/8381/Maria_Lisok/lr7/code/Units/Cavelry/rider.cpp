#include "rider.h"

Rider::Rider(){
    name = "Rider";
    attributes = new Attributes();
    attributes->setAllAttributes(70, 30, 2);
}

string Rider::getName()
{
    return "rider";
}

Unit *Rider::copyItem()
{
    return new Rider(*this);
}

UnitsType Rider::getTypeEnum() const
{
    return RIDER;
}
