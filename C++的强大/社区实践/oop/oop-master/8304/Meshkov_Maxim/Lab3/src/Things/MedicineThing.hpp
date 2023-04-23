#pragma once

#include "Thing.hpp"

class MedicineThing : public Thing {
public:
    void applyTo(Unit &unit) const override {
        unit.modifyHealth(+10);
    }
};