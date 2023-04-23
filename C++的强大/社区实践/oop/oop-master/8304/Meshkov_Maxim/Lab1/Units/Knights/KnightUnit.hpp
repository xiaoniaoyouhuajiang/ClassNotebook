#pragma once

#include "../BaseUnit.hpp"

class KnightUnit : public BaseUnit {
public:
    KnightUnit() {
        m_hit = 22;
        m_icesWhenAttacks = false;
        m_attackRange = 1;
    }
};
