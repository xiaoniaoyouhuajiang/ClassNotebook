#include "dragonArmorUpdateLogic.hpp"
using namespace unit;

void DragonArmorUpdateLogic::updateUnit(std::shared_ptr<unit::Unit> unit) const
{
   HeavyArmorFactory factory;
   unit->setArmor(factory.createArmor());
}


std::shared_ptr<StrategyPattern> DragonArmorUpdateLogic::clone() const
{
    return std::make_shared<DragonArmorUpdateLogic>();
}
