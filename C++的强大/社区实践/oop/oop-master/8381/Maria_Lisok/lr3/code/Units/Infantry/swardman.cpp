#include "swardman.h"

Swardman::Swardman(){
    name = "Swardman";
    attributes = new Attributes();
    attributes->setAllAttributes(50, 100, 10);
}

string Swardman::getName()
{
    return "swardman";
}

Unit *Swardman::copyItem()
{
    return new Swardman(*this);
}

UnitsType Swardman::getTypeEnum() const
{
    return SWARDMAN;
}
