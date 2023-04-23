#include "baseparam.h"
BaseParam::BaseParam(int baseNumb, int unitCount, const int maxCount, int health, const int x, const int y, int unitCurr, vector<UnitParam*> units):
    baseNumb(baseNumb), unitCount(unitCount), maxCount(maxCount), health(health), x(x), y(y), unitCurr(unitCurr), units(units)
{}

int BaseParam::getBaseNumb() const
{
    return baseNumb;
}

int BaseParam::getUnitCount() const
{
    return unitCount;
}

int BaseParam::getMaxCount() const
{
    return maxCount;
}

int BaseParam::getHealth() const
{
    return health;
}

int BaseParam::getX() const
{
    return x;
}

int BaseParam::getY() const
{
    return y;
}

int BaseParam::getUnitCurr() const
{
    return unitCurr;
}

vector<UnitParam*> BaseParam::getUnits() const
{
    return units;
}
