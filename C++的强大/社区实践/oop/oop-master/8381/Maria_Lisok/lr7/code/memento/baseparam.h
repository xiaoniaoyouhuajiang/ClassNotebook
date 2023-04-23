#ifndef BASEPARAM_H
#define BASEPARAM_H

#include "unitparam.h"

#include <vector>


class BaseParam
{
public:
    BaseParam(int baseNumb, int unitCount, const int maxCount, int health, const int x, const int y, int unitCurr, vector<UnitParam*> units);

    int getBaseNumb() const;

    int getUnitCount() const;

    int getMaxCount() const;

    int getHealth() const;

    int getX() const;

    int getY() const;

    int getUnitCurr() const;

    vector<UnitParam*> getUnits() const;

private:
    int baseNumb;
    int unitCount;
    const int maxCount;
    int health;
    const int x, y;
    int unitCurr;
    vector<UnitParam*> units;
};

#endif // BASEPARAM_H
