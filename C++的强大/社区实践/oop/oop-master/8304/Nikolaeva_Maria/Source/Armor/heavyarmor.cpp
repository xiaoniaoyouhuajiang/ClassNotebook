#include "heavyarmor.h"


HeavyArmor::HeavyArmor()
{
    resistance = HEAVY_ARMOR;
}


double HeavyArmor::getResistance() const
{
    return this->resistance;
}


Armor* HeavyArmor::clone()
{
    HeavyArmor* armor = new HeavyArmor;
    armor->resistance = this->resistance;

    return armor;
}
