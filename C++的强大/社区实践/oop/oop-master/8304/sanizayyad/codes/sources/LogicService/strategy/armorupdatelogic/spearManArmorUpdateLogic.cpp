#include "SpearManArmorUpdateLogic.hpp"

using namespace unit;


void SpearManArmorUpdateLogic::updateUnit(std::shared_ptr<unit::Unit> unit) const
{
   LightArmorFactory factory;
   unit->setArmor(factory.createArmor());
}


std::shared_ptr<StrategyPattern> SpearManArmorUpdateLogic::clone() const
{
    return std::make_shared<SpearManArmorUpdateLogic>();
}
