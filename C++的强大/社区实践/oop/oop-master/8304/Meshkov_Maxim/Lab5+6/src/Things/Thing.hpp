#pragma once

#include <string>

#include "../Units/Unit.hpp"

class Thing {
public:
    virtual std::string getName() const = 0;
    virtual void applyTo(Unit &unit) const = 0;
};

Unit &operator<<(Unit &unit, const Thing &thing);
