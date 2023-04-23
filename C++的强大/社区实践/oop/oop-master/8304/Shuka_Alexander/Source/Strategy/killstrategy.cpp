#include "killstrategy.h"

using namespace unit;


void KillStrategy::changeUnit(std::shared_ptr<Unit> unit) const
{
    unit->toHurt(unit->getHealthPoints());
}


std::shared_ptr<Strategy> KillStrategy::clone() const
{
    return std::make_shared<KillStrategy>();
}
