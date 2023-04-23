
#include "mediumarmorfactory.hpp"

std::shared_ptr<Armor> MediumArmorFactory::createArmor() const
{
    return std::make_shared<MediumArmor>();

}
