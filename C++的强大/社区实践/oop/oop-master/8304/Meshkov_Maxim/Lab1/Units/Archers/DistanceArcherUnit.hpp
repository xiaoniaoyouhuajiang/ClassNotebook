#pragma once

#include "ArcherUnit.hpp"

class DistanceArcherUnit : public ArcherUnit {
public:
    DistanceArcherUnit() {
        m_hit = 5;
        m_attackRange = 10;
    }

    std::string getName() const override {
        return "Distance Archer";
    }

    std::shared_ptr<Unit> createNewOfSameType() const override;
    std::shared_ptr<Unit> createCopy() const override;
};
