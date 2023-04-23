
#include "lightarmorfactory.hpp"

std::shared_ptr<Armor> LightArmorFactory::createArmor() const
{
    return std::make_shared<LightArmor>();

}
