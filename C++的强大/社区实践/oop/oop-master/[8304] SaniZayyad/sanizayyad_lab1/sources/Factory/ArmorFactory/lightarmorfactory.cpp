
#include "lightarmorfactory.hpp"

std::unique_ptr<Armor> LightArmorFactory::createArmor()
{
    std::unique_ptr<Armor> armor(new LightArmor);

    return armor;
}
