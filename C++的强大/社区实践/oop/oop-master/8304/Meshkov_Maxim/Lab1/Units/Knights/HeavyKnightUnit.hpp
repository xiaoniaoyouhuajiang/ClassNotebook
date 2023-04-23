#pragma once

#include "KnightUnit.hpp"

class HeavyKnightUnit : public KnightUnit {
public:
    HeavyKnightUnit() {
        m_armor = 5;
        m_moveRange = 1;
    }

    std::string getName() const override {
        return "Heavy Knight";
    }

    std::shared_ptr<Unit> createNewOfSameType() const override;
    std::shared_ptr<Unit> createCopy() const override;
};
