#pragma once

#include "Unit.hpp"

class BaseUnit : public Unit {
public:
    int getHealth() const override {
        return m_health;
    }
    int getHit() const override {
        return m_hit;
    }
    bool icesWhenAttacks() const override {
        return m_icesWhenAttacks;
    }
    int getArmor() const override {
        return m_armor;
    }
    int getMoveRange() const override {
        return m_moveRange;
    }
    int getAttackRange() const override {
        return m_attackRange;
    }
    bool isIced() const override {
        return m_isIced;
    }

protected:
    static const int maxHealth = 20;
    int m_health = maxHealth;

    int m_hit = 0;
    bool m_icesWhenAttacks = false;
    int m_armor = 0;
    int m_moveRange = 0;
    int m_attackRange = 0;
    bool m_isIced = false;

    BaseUnit &operator=(const BaseUnit &) = default;
};
