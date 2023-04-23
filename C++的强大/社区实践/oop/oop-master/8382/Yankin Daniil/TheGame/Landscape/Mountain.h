#pragma once

#include "Landscape/Landscape.h"


class Mountain : public Landscape
{
public:
    Mountain(Point point);
    bool movementAccess() override;
    uint16_t getObjectType() override;
};
