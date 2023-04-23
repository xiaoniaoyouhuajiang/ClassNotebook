#pragma once

#include "Thing.hpp"

class MedicineThing : public Thing {
public:
    std::string getName() const override {
        return "Medicine Thing";
    }
    void applyTo(Unit &unit) const override {
        unit.modifyHealth(+10);
    }
};