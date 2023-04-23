#pragma once

#include "Landscape/Landscape.h"


class Plain : public Landscape
{
public:
    Plain(Point point);
    bool movementAccess() override;
    uint16_t getObjectType() override;
};
