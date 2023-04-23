#include "heavyarmorfactory.hpp"

std::shared_ptr<Armor> HeavyArmorFactory::createArmor() const
{
    return std::make_shared<HeavyArmor>();

}
