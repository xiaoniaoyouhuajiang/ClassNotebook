 #include "SwordManArmorUpdateLogic.hpp"

using namespace unit;

void SwordManArmorUpdateLogic::updateUnit(std::shared_ptr<unit::Unit> unit) const
{
    LightArmorFactory factory;
    unit->setArmor(factory.createArmor());
}


std::shared_ptr<StrategyPattern> SwordManArmorUpdateLogic::clone() const
{
    return std::make_shared<SwordManArmorUpdateLogic>();
}
