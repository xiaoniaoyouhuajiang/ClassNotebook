#include "mediumarmor.hpp"


MediumArmor::MediumArmor()
{
    armorType = "Medium Armor";
    resistance = MEDIUM_ARMOR;
}


double MediumArmor::getResistance() const
{
    return resistance;
}

std::string MediumArmor::getAmorType() const
{
    return armorType;
}


MediumArmor::MediumArmor(const MediumArmor& armor)
{
    this->doCopy(armor);
}


std::shared_ptr<Armor> MediumArmor::clone() const
{
    return std::make_shared<MediumArmor>(*this);
}


MediumArmor& MediumArmor::operator=(const MediumArmor& armor)
{
    if (this == &armor) {
        return *this;
    }

    this->doCopy(armor);

    return *this;
}
