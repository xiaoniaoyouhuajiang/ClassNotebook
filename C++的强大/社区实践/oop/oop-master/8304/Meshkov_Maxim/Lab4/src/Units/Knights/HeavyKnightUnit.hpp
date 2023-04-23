#pragma once

#include "KnightUnit.hpp"
#include "../ConcreteUnitFactory.hpp"

class HeavyKnightUnit : public KnightUnit {
public:
    HeavyKnightUnit() {
        m_armor = 5;
        m_moveRange = 1;
    }

    std::string getName() const override {
        return "Heavy Knight";
    }

    std::shared_ptr<UnitFactory> createUnitFactory() const override {
        return std::make_shared<ConcreteUnitFactory<HeavyKnightUnit>>();
    }
    std::shared_ptr<Unit> createCopy() const override {
        return std::make_shared<HeavyKnightUnit>(*this);
    }
};
