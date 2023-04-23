#pragma once

#include "Thing.hpp"

class PowerfulMedicineThing : public Thing {
public:
    void applyTo(Unit &unit) const override {
        unit.modifyHealth(unit.getMaxHealth());
    }
};