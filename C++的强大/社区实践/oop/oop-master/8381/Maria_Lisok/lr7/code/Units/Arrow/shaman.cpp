#include "shaman.h"

Shaman::Shaman(){
    name = "Shaman";
    attributes = new Attributes();
    attributes->setAllAttributes(10, 20, 5);
}

string Shaman::getName()
{
    return "shaman";
}

Unit *Shaman::copyItem()
{
    return new Shaman(*this);
}

UnitsType Shaman::getTypeEnum() const
{
    return SHAMAN;
}
