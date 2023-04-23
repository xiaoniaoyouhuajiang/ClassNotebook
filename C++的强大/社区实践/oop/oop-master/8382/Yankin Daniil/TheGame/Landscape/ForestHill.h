#pragma once

#include "Landscape/Landscape.h"


class ForestHill : public Landscape
{
public:
    ForestHill(Point point);
    bool movementAccess() override;
    uint16_t getObjectType() override;
};
