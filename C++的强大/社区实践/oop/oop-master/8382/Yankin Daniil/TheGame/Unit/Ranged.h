#pragma once

#include "Unit.h"


class Ranged : public Unit
{
public:
    Ranged(Point point, Base* base);
    Ranged(UnitSnapshot& snapshot, Base* base);
    Ranged(UnitSnapshot& snapshot, UnitGroup* group);
    uint16_t getUnitClass() override;
    double classAttackModifier(Object* enemy) override;
};



class Archer : public Ranged
{
public:
    Archer(Point point, Base* base);
    Archer(UnitSnapshot& snapshot, Base* base);
    Archer(UnitSnapshot& snapshot, UnitGroup* group);
    ~Archer();
    uint16_t getObjectType() override;
    double typeAttackModifier(Object* enemy) override;
};


class Crossbowman : public Ranged
{
public:
    Crossbowman(Point point, Base* base);
    Crossbowman(UnitSnapshot& snapshot, Base* base);
    Crossbowman(UnitSnapshot& snapshot, UnitGroup* group);
    ~Crossbowman();
    uint16_t getObjectType() override;
    double typeAttackModifier(Object* enemy) override;
};


class ScoutCavalry : public Ranged
{
public:
    ScoutCavalry(Point point, Base* base);
    ScoutCavalry(UnitSnapshot& snapshot, Base* base);
    ScoutCavalry(UnitSnapshot& snapshot, UnitGroup* group);
    ~ScoutCavalry();
    uint16_t getObjectType() override;
    double typeAttackModifier(Object* enemy) override;
};
