#pragma once

#include "Thing.hpp"

class MicroMedicineThing : public Thing {
public:
    void applyTo(Unit &unit) const override {
        unit.modifyHealth(+2);
    }
};