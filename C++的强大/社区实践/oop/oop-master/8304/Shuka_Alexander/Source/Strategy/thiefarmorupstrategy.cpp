#include "thiefarmorupstrategy.h"

using namespace unit;


void ThiefArmorUpStrategy::changeUnit(std::shared_ptr<Unit> unit) const
{
    LightArmorFactory factory;
    unit->setArmor(factory.createArmor());
}


std::shared_ptr<Strategy> ThiefArmorUpStrategy::clone() const
{
    return std::make_shared<ThiefArmorUpStrategy>();
}
