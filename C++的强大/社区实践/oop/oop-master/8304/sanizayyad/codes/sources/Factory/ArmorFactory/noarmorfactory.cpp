#include "noarmorfactory.hpp"

std::shared_ptr<Armor> NoArmorFactory::createArmor() const
{
    return std::make_shared<NoArmor>();

}
