#pragma once

#include "MageUnit.hpp"
#include "../ConcreteUnitFactory.hpp"

class FireMageUnit : public MageUnit {
public:
    FireMageUnit() {
        m_hit = 5;
        m_icesWhenAttacks = false;
        m_attackRange = 10;
    }

    std::string getName() const override {
        return "Fire Mage";
    }

    std::shared_ptr<UnitFactory> createUnitFactory() const override {
        return std::make_shared<ConcreteUnitFactory<FireMageUnit>>();
    }
    std::shared_ptr<Unit> createCopy() const override {
        return std::make_shared<FireMageUnit>(*this);
    }
};
