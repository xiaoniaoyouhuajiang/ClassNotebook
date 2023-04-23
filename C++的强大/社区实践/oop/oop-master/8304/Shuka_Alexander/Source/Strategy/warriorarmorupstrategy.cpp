#include "warriorarmorupstrategy.h"

using namespace unit;


void WarriorArmorUpStrategy::changeUnit(std::shared_ptr<Unit> unit) const
{
    MediumArmorFactory factory;
    unit->setArmor(factory.createArmor());
}


std::shared_ptr<Strategy> WarriorArmorUpStrategy::clone() const
{
    return std::make_shared<WarriorArmorUpStrategy>();
}
