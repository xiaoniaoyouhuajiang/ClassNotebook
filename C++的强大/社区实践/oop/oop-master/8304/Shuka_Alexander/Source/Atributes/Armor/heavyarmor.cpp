#include "heavyarmor.h"


HeavyArmor::HeavyArmor()
{
    resistance = HEAVY_ARMOR;
}


HeavyArmor::HeavyArmor(const HeavyArmor& armor)
{
    this->doCopy(armor);
}


HeavyArmor& HeavyArmor::operator=(const HeavyArmor& armor)
{
    if (this == &armor) {
        return *this;
    }

    this->doCopy(armor);

    return *this;
}


std::shared_ptr<Armor> HeavyArmor::clone() const
{
    return std::make_shared<HeavyArmor>(*this);
}


double HeavyArmor::getResistance() const
{
    return resistance;
}
