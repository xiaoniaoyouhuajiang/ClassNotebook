#include "archerArmorUpdateLogic.hpp"

using namespace unit;
void ArcherArmorUpdateLogic::updateUnit(std::shared_ptr<unit::Unit> unit) const
{
   LightArmorFactory factory;
   unit->setArmor(factory.createArmor());
}


std::shared_ptr<StrategyPattern> ArcherArmorUpdateLogic::clone() const
{
    return std::make_shared<ArcherArmorUpdateLogic>();
}
