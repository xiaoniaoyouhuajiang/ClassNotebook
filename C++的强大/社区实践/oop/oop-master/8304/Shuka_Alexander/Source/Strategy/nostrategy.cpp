#include "nostrategy.h"

using namespace unit;


void NoStrategy::changeUnit(std::shared_ptr<Unit> unit) const
{
    Q_UNUSED(unit);
}


std::shared_ptr<Strategy> NoStrategy::clone() const
{
    return std::make_shared<NoStrategy>();
}
