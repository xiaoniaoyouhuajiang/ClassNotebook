#pragma once

#include "Thing.hpp"

class PowerfulMedicineThing : public Thing {
public:
    std::string getName() const override {
        return "Powerful Medicine Thing";
    }
    void applyTo(Unit &unit) const override {
        unit.modifyHealth(unit.getMaxHealth());
    }
};