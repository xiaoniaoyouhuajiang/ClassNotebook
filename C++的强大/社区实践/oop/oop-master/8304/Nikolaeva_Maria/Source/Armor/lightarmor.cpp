#include "lightarmor.h"


LightArmor::LightArmor()
{
    resistance = LIGHT_ARMOR;
}


double LightArmor::getResistance() const
{
    return this->resistance;
}


Armor* LightArmor::clone()
{
    LightArmor* armor = new LightArmor;
    armor->resistance = this->resistance;

    return armor;
}
