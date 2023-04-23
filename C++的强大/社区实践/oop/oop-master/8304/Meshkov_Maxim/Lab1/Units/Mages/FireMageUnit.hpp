#pragma once

#include "MageUnit.hpp"

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

    std::shared_ptr<Unit> createNewOfSameType() const override;
    std::shared_ptr<Unit> createCopy() const override;
};
