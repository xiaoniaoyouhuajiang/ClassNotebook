#pragma once

#include "ArcherUnit.hpp"
#include "../ConcreteUnitFactory.hpp"

class DistanceArcherUnit : public ArcherUnit {
public:
    DistanceArcherUnit() {
        m_hit = 5;
        m_attackRange = 10;
    }

    std::string getName() const override {
        return "Distance Archer";
    }

    std::shared_ptr<UnitFactory> createUnitFactory() const override {
        return std::make_shared<ConcreteUnitFactory<DistanceArcherUnit>>();
    }
    std::shared_ptr<Unit> createCopy() const override {
        return std::make_shared<DistanceArcherUnit>(*this);
    }
};
