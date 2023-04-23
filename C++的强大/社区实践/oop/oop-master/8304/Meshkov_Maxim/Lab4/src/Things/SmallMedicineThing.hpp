#pragma once

#include "Thing.hpp"

class SmallMedicineThing : public Thing {
public:
    std::string getName() const override {
        return "Small Medicine Thing";
    }
    void applyTo(Unit &unit) const override {
        unit.modifyHealth(+5);
    }
};