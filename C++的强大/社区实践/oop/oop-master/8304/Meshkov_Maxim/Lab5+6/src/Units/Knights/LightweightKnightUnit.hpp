#pragma once

#include "KnightUnit.hpp"
#include "../ConcreteUnitFactory.hpp"

class LightweightKnightUnit : public KnightUnit {
public:
    LightweightKnightUnit() {
        m_armor = 3;
        m_moveRange = 2;
    }

    std::string getName() const override {
        return "Lightweight Knight";
    }

    std::shared_ptr<UnitFactory> createUnitFactory() const override {
        return std::make_shared<ConcreteUnitFactory<LightweightKnightUnit>>();
    }
    std::shared_ptr<Unit> createCopy() const override {
        return std::make_shared<LightweightKnightUnit>(*this);
    }
};
