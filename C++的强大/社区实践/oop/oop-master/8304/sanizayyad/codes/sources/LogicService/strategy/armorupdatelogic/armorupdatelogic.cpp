#include "armorupdatelogic.hpp"

using namespace unit;

void ArmorUpdateLogic::updateUnit(std::shared_ptr<unit::Unit> unit) const
{
    unit->setArmor(this->armor->clone());
}
