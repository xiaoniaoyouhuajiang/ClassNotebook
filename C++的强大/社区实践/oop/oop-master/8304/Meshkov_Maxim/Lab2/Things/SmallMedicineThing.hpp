#pragma once

#include "Thing.hpp"

class SmallMedicineThing : public Thing {
public:
    void applyTo(Unit &unit) const override {
        unit.modifyHealth(+5);
    }
};