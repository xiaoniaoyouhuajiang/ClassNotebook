#pragma once

#include "ILandscape.h"


class Landscape : public ILandscape
{
public:
    Landscape(Point point);
    Point getPoint() override;
    int16_t getMovementCost() override;

protected:
    Point point;
    int16_t movementCost;
};
