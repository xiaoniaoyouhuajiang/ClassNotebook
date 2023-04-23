#pragma once

#include "KnightUnit.hpp"

class LightweightKnightUnit : public KnightUnit {
public:
    LightweightKnightUnit() {
        m_armor = 3;
        m_moveRange = 2;
    }

    std::string getName() const override {
        return "Lightweight Knight";
    }

    std::shared_ptr<Unit> createNewOfSameType() const override;
    std::shared_ptr<Unit> createCopy() const override;
};
