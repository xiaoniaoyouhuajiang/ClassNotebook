#pragma once

#include "Unit.hpp"

class BaseUnit : public Unit {
public:
    std::optional<int> getPlayer() const override;

    int getHealth() const override {
        return m_health;
    }
    int getMaxHealth() const override {
        return 20;
    }
    void modifyHealth(int change) override;
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
    void ice() override;

    std::set<FieldPosition> findPossibleMoves(FieldPosition unitPosition, const Field &field) const override;
    std::set<FieldPosition> findPossibleAttacks(FieldPosition unitPosition, const Field &field) const override;

    void attack(FieldPosition victimPosition, Field &field) override;

    std::weak_ptr<const Base> getBase() const override;
    void setBase(std::weak_ptr<Base> base) override ;
    void notifyAboutDeletionFromField() override;

protected:
    int m_health = getMaxHealth();

    int m_hit = 0;
    bool m_icesWhenAttacks = false;
    int m_armor = 0;
    int m_moveRange = 0;
    int m_attackRange = 0;
    bool m_isIced = false;

    std::weak_ptr<Base> m_base;
    std::optional<int> m_player;

    BaseUnit &operator=(const BaseUnit &) = default;
};
