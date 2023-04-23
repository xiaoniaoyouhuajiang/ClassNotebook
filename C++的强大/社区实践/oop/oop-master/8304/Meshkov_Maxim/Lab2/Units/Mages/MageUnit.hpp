#pragma once

#include "../BaseUnit.hpp"

class MageUnit : public BaseUnit {
public:
    MageUnit() {
        m_armor = 0;
        m_moveRange = 4;
    }
};