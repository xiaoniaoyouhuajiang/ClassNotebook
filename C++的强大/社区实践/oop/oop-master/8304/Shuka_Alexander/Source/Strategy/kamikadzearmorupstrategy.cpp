#include "kamikadzearmorupstrategy.h"

#include <qglobal.h>

using namespace unit;


void KamikadzeArmorUpStrategy::changeUnit(std::shared_ptr<Unit> unit) const
{
    Q_UNUSED(unit);
}


std::shared_ptr<Strategy> KamikadzeArmorUpStrategy::clone() const
{
    return std::make_shared<KamikadzeArmorUpStrategy>();
}
