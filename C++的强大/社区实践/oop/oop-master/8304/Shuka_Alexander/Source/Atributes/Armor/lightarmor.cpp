#include "lightarmor.h"


LightArmor::LightArmor()
{
    resistance = LIGHT_ARMOR;
}


double LightArmor::getResistance() const
{
    return resistance;
}


std::shared_ptr<Armor> LightArmor::clone() const
{
    return std::make_shared<LightArmor>(*this);
}


LightArmor::LightArmor(const LightArmor& armor)
{
    this->doCopy(armor);
}


LightArmor& LightArmor::operator=(const LightArmor& armor)
{
    if (this == &armor) {
        return *this;
    }

    this->doCopy(armor);

    return *this;
}
