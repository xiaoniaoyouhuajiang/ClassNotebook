#pragma once

#include <string>

#include "../Units/Unit.hpp"

class Thing {
public:
    virtual void applyTo(Unit &unit) const = 0;
};

Unit &operator<<(Unit &unit, const Thing &thing);
