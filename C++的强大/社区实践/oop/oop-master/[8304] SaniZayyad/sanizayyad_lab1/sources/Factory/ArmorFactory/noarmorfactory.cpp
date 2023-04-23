#include "noarmorfactory.hpp"

std::unique_ptr<Armor> NoArmorFactory::createArmor()
{
    std::unique_ptr<Armor> armor(new NoArmor);

    return armor;
}
