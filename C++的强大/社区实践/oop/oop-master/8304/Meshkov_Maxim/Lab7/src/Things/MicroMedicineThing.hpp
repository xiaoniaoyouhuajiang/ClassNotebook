#pragma once

#include "Thing.hpp"

class MicroMedicineThing : public Thing {
public:
    std::string getName() const override {
        return "Micro Medicine Thing";
    }
    void applyTo(Unit &unit) const override {
        unit.modifyHealth(+2);
    }
};