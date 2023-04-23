#pragma once

#include "Landscape/Landscape.h"


class Hill : public Landscape
{
public:
    Hill(Point point);
    bool movementAccess() override;
    uint16_t getObjectType() override;
};
