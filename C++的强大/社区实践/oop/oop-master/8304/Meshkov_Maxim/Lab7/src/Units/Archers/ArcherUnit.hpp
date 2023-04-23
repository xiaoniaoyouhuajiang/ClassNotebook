#pragma once

#include "../BaseUnit.hpp"

class ArcherUnit : public BaseUnit{
public:
    ArcherUnit() {
        m_icesWhenAttacks = false;
        m_armor = 1;
        m_moveRange = 3;
    }
};
