#pragma once

#include <vector>
#include <set>
#include <cmath>
#include "Unit.h"

#define MAX_GROUP_SIZE 4

class UnitGroup : public IUnit
{
public:
    class UnitGroupSnapshot;

    UnitGroup(std::vector <Unit*> details);
    UnitGroup(UnitGroupSnapshot& snapshot, Base* base);
    ~UnitGroup();

    uint16_t getUnitClass() override;
    uint16_t getObjectType() override;

    Point getPoint() override;
    void setPoint(Point point) override;
    Player* getPlayer() override;
    Base* getBase() override;

    uint16_t getMaxHealth() override;
    uint16_t getHealth() override;
    uint16_t getAttack() override;
    uint16_t getAttackRadius() override;
    uint16_t getArmor() override;
    uint16_t getMaxMovePoints() override;
    uint16_t getMovePoints() override;

    uint16_t giveDamage(IUnit* enemy) override;
    uint16_t giveDamage(Base* enemy) override;
    bool takeDamage(uint16_t damage) override;

    void join(Unit* unit, bool moveTo);
    void join(UnitGroup* group, bool moveTo);

    uint16_t getMaxGroupSize();
    uint16_t getGroupSize();

    void setAttacked() override;
    void unsetAttacked() override;
    bool checkAttacked() override;

private:
    void setMovePoints(uint16_t points) override;

    void smallHeal(uint16_t healSize = 10) override;
    void fullHeal() override;
    void attackModification(int16_t modSize) override;
    void armorModification(int16_t modSize) override;
    void renewMovePoints() override;

    std::set <Unit*> unitSet;
    uint16_t maxGroupSize;

    Base* base;
};


class UnitGroup::UnitGroupSnapshot : public Snapshot {
    friend class UnitGroup;

public:
    UnitGroupSnapshot(UnitGroup& group);
    UnitGroupSnapshot(std::ifstream& stream);
    friend std::ofstream& operator<<(std::ofstream& stream, const UnitGroup::UnitGroupSnapshot& snapshot);

private:
    uint16_t objectType;
    Point point;
    uint16_t unitCount;
    std::vector<Unit::UnitSnapshot> unitSnapVector;
};
