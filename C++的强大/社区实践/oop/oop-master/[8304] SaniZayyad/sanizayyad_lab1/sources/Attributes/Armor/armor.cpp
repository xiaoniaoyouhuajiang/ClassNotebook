#include "armor.hpp"

void Armor::doCopy(const Armor& armor)
{
    this->resistance = armor.resistance;
}

void Armor::getArmorInfo()
{
    std::cout<< "Defense Skills: ";
    std::cout<< "\n    Armor Type: " << armorType;
    std::cout<< "\n    Armor Resistance: " << resistance<<"\n";
}
