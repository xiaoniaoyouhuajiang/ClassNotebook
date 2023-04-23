#pragma once

#include "ArcherUnit.hpp"
#include "../ConcreteUnitFactory.hpp"

class PowerfulArcherUnit : public ArcherUnit {
public:
    PowerfulArcherUnit() {
        m_hit = 8;
        m_attackRange = 6;
    }

    std::string getName() const override {
        return "Powerful Archer";
    }

    std::shared_ptr<UnitFactory> createUnitFactory() const override {
        return std::make_shared<ConcreteUnitFactory<PowerfulArcherUnit>>();
    }
    std::shared_ptr<Unit> createCopy() const override {
        return std::make_shared<PowerfulArcherUnit>(*this);
    }
};
