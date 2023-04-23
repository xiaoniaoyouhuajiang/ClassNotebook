#ifndef STANDINGUNIT_H
#define STANDINGUNIT_H

#include "Unit/unit.h"


class StandingUnit : public Unit
{
public:
    virtual ~StandingUnit() = default;

    bool move(int dx, int dy) override;
    bool isFlying() override;
};

#endif // STANDINGUNIT_H
