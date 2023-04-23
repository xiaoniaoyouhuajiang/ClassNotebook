#pragma once

#include <set>

#include "Units/UnitFactory.hpp"
#include "FieldPosition.hpp"
class Field;
#include "Creature.hpp"

class Base : public Creature {
public:
    Base(int player, Field &field, FieldPosition basePosition);

    std::string getName() const override {
        return "Base";
    }

    int getCreationAbility() const {
        return m_creationAbility;
    }
    void setCreationAbility(int creationAbility);
    bool hasSpaceToCreate(Field &field, FieldPosition basePosition) const;
    FieldPosition createUnit(const std::shared_ptr<const UnitFactory> &unitFactory, FieldPosition basePosition, Field &field);
    void reactOnUnitDeletion(const Unit *notifier);

    std::optional<int> getPlayer() const override {
        return m_player;
    }

    int getHealth() const override {
        return m_health;
    }
    int getMaxHealth() const override {
        return 20;
    }
    void modifyHealth(int change) override;
    void setHealth(int health) override;

private:
    int m_player;
    int m_creationAbility = 8;
    int m_health = getMaxHealth();

    std::set<const Unit *> m_notifiers;
};
