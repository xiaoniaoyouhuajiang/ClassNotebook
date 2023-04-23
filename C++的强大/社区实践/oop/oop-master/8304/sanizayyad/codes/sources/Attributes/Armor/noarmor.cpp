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


std::shared_ptr<Armor> NoArmor::clone() const
{
    return std::make_shared<NoArmor>(*this);
}


NoArmor& NoArmor::operator=(const NoArmor& armor)
{
    if (this == &armor) {
        return *this;
    }

    this->doCopy(armor);

    return *this;
}
