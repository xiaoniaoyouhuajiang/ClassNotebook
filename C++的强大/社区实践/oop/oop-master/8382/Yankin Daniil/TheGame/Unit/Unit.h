#pragma once

#include "IUnit.h"
#include "Trivia/Attributes.h"
#include "Trivia/Snapshot.h"

class Player;
class Base;
class UnitGroup;

class Unit : public IUnit
{
    friend class UnitGroup;

public:
    class UnitSnapshot;

    Unit(Point point, Base* base);
    Unit(UnitSnapshot& snapshot, Base* base);
    Unit(UnitSnapshot& snapshot, UnitGroup* group);
    ~Unit();

    Point getPoint() override;
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

    void setAttacked() override;
    void unsetAttacked() override;
    bool checkAttacked() override;

    virtual double classAttackModifier(Object* enemy) = 0;
    virtual double typeAttackModifier(Object* enemy) = 0;

    static uint16_t generateUnitType();

protected:
    void setPoint(Point point) override;
    void setMovePoints(uint16_t points) override;

    void smallHeal(uint16_t healSize = 10) override;
    void fullHeal() override;
    void attackModification(int16_t modSize) override;
    void armorModification(int16_t modSize) override;
    void renewMovePoints() override;


    Point point;

    union {
        Base* base;
        UnitGroup* group;
    };
    bool isGroup;

    Health health;
    Strength strength;
    Armor armor;
    MovePoints movePoints;

    bool attacked;
};


class Unit::UnitSnapshot : public Snapshot {
    friend class Unit;

public:
    UnitSnapshot(Unit& unit);
    UnitSnapshot(std::ifstream& stream);
    friend std::ofstream& operator<<(std::ofstream& stream, const Unit::UnitSnapshot& snapshot);
    uint16_t getObjectType() const;

private:
    uint16_t objectType;
    Point point;
    Health health;
    Strength strength;
    Armor armor;
    MovePoints movePoints;
    bool attacked;
};


class Unit::UnitSnapshot : public Snapshot {
    friend class Unit;

public:
    UnitSnapshot(Unit& unit);
    UnitSnapshot(std::ifstream& stream);
    friend std::ofstream& operator<<(std::ofstream& stream, const Unit::UnitSnapshot& snapshot);
    uint16_t getObjectType() const;

private:
    uint16_t objectType;
    Point point;
    Health health;
    Strength strength;
    Armor armor;
    MovePoints movePoints;
};


enum UnitClasses {
    UNIT_MELEE,
    UNIT_RANGED,
    UNIT_SIEGE_ENGINE
};
