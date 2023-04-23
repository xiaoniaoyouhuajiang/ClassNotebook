#pragma once

#include "Landscape/Landscape.h"


class Water : public Landscape
{
public:
    Water(Point point);
    bool movementAccess() override;
    uint16_t getObjectType() override;
};
