#include "ork.h"

Ork::Ork(){
    name = "Ork";
    attributes = new Attributes();
    attributes->setAllAttributes(100, 50, 10);
}

string Ork::getName()
{
    return "ork";
}

Unit *Ork::copyItem()
{
    return new Ork(*this);
}

UnitsType Ork::getTypeEnum() const
{
    return ORK;
}
