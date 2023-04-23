#include "noarmor.hpp"

NoArmor::NoArmor()
{
    armorType = "No Armor";
    resistance = NO_ARMOR;
}


double NoArmor::getResistance() const
{
    return resistance;
}

std::string NoArmor::getAmorType() const
{
    return armorType;
}

NoArmor::NoArmor(const NoArmor& armor)
{
    this->doCopy(armor);
}


std::unique_ptr<Armor> NoArmor::clone()
{
    std::unique_ptr<Armor> armor(new NoArmor(*this));
    return armor;
}


NoArmor& NoArmor::operator=(const NoArmor& armor)
{
    if (this == &armor) {
        return *this;
    }

    this->doCopy(armor);

    return *this;
}
