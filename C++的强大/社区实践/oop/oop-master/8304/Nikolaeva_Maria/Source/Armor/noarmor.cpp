#include "noarmor.h"


NoArmor::NoArmor()
{
    resistance = NO_ARMOR;
}


double NoArmor::getResistance() const
{
    return this->resistance;
}


Armor* NoArmor::clone()
{
    NoArmor* armor = new NoArmor;
    armor->resistance = this->resistance;

    return armor;
}
