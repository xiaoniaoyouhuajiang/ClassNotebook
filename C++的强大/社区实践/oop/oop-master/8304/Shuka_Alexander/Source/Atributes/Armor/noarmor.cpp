#include "noarmor.h"


NoArmor::NoArmor()
{
    resistance = NO_ARMOR;
}


double NoArmor::getResistance() const
{
    return resistance;
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
