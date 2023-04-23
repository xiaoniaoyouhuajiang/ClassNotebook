#include "knigth.h"

Knigth::Knigth(){
    name = "Knigth";
    attributes = new Attributes();
    attributes->setAllAttributes(45, 50, 3);
}

string Knigth::getName()
{
    return "knigth";
}

Unit *Knigth::copyItem()
{
    return new Knigth(*this);
}

UnitsType Knigth::getTypeEnum() const
{
    return KNIGTH;
}
