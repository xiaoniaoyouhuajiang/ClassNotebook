#pragma once

#include "Object/Object.h"


class ILandscape : public Object
{
public:
    uint16_t getGroupType() override;
    virtual bool movementAccess() = 0;
    virtual int16_t getMovementCost() = 0;
};
