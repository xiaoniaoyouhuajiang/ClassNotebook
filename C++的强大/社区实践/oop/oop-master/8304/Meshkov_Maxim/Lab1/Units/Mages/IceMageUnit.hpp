#pragma once

#include "MageUnit.hpp"

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

    std::shared_ptr<Unit> createNewOfSameType() const override;
    std::shared_ptr<Unit> createCopy() const override;
};
