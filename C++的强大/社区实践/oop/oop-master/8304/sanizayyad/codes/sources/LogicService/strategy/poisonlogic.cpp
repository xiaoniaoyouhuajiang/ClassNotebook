#include "poisonlogic.hpp"

using namespace unit;
void PoisonLogic::updateUnit(std::shared_ptr<unit::Unit> unit) const
{
   unit->makeDamage(unit->getHealthPoints());
   //supposed to be addtion
}


std::shared_ptr<StrategyPattern> PoisonLogic::clone() const
{
    return std::make_shared<PoisonLogic>();
}
