#pragma once

#include <set>
#include "Object/Object.h"
#include "Unit/UnitHeader.h"
#include "Game/Game.h"

#define MAX_UNIT_COUNT_AT_BASE 4

class Player;
class Cell;

class Base : public Object
{
    friend class Game::Saver;

public:
    class BaseSnapshot;

    Base(Point point, Player* player);
    Base(BaseSnapshot& snapshot, Player* player);
    ~Base();

    uint16_t getGroupType() override;
    uint16_t getObjectType() override;

    Player* getPlayer();
    Point getPoint() override;

    uint16_t getMaxHealth();
    uint16_t getHealth();
    uint16_t getAttack();
    uint16_t getArmor();

    uint16_t giveDamage(IUnit *enemy);
    bool takeDamage(uint16_t damage);

    void produceUnit(uint16_t unitType);

    bool isBelowUnitMax();
    void addUnit(IUnit* unit);
    void removeUnit(IUnit* unit);

    uint16_t getUnitCount();
    uint16_t getMaxUnitCount();

private:
    Point point;

    Player* player;
    Health health;
    Strength strength;
    Armor armor;

    UnitFactory unitFactory;
    std::set <IUnit*> unitSet;
    uint16_t maxUnitCount;
};


class Base::BaseSnapshot : public Snapshot {
    friend class Base;

public:
    BaseSnapshot(Base& base);
    BaseSnapshot(std::ifstream& stream);
    friend std::ofstream& operator<<(std::ofstream& stream, const Base::BaseSnapshot& snapshot);

private:
    Point point;
    Health health;
    Strength strength;
    Armor armor;
};
