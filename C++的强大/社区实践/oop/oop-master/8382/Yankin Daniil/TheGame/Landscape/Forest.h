#pragma once

#include "Landscape/Landscape.h"


class Forest : public Landscape
{
public:
    Forest(Point point);
    bool movementAccess() override;
    uint16_t getObjectType() override;
};
