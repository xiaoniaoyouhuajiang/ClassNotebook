#pragma once

#include "MageUnit.hpp"
#include "../ConcreteUnitFactory.hpp"

class IceMageUnit : public MageUnit {
public:
    IceMageUnit() {
        m_icesWhenAttacks = true;
        m_hit = 2;
        m_attackRange = 10;
    }

    std::string getName() const override {
        return "Ice Mage";
    }

    std::shared_ptr<UnitFactory> createUnitFactory() const override {
        return std::make_shared<ConcreteUnitFactory<IceMageUnit>>();
    }
    std::shared_ptr<Unit> createCopy() const override {
        return std::make_shared<IceMageUnit>(*this);
    }
};
