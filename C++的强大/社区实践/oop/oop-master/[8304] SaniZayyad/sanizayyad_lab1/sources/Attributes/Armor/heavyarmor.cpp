#include "heavyarmor.hpp"

HeavyArmor::HeavyArmor()
{
    armorType = "Heavy Armor";
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


std::unique_ptr<Armor> HeavyArmor::clone()
{
    std::unique_ptr<Armor> armor(new HeavyArmor(*this));
    return armor;
}


double HeavyArmor::getResistance() const
{
    return resistance;
}

std::string HeavyArmor::getAmorType() const
{
    return armorType;
}
