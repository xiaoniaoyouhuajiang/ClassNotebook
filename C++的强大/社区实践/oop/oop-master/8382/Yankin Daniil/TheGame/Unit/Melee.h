#pragma once

#include "Unit.h"


class Melee : public Unit
{
public:
    Melee(Point point, Base* base);
    Melee(UnitSnapshot& snapshot, Base* base);
    Melee(UnitSnapshot& snapshot, UnitGroup* group);
    uint16_t getUnitClass() override;
    double classAttackModifier(Object* enemy) override;
};



class Swordsman : public Melee
{
public:
    Swordsman(Point point, Base* base);
    Swordsman(UnitSnapshot& snapshot, Base* base);
    Swordsman(UnitSnapshot& snapshot, UnitGroup* group);
    ~Swordsman();
    uint16_t getObjectType() override;
    double typeAttackModifier(Object* enemy) override;
};


class Pikeman : public Melee
{
public:
    Pikeman(Point point, Base* base);
    Pikeman(UnitSnapshot& snapshot, Base* base);
    Pikeman(UnitSnapshot& snapshot, UnitGroup* group);
    ~Pikeman();
    uint16_t getObjectType() override;
    double typeAttackModifier(Object* enemy) override;
};


class ShockCavalry : public Melee
{
public:
    ShockCavalry(Point point, Base* base);
    ShockCavalry(UnitSnapshot& snapshot, Base* base);
    ShockCavalry(UnitSnapshot& snapshot, UnitGroup* group);
    ~ShockCavalry();
    uint16_t getObjectType() override;
    double typeAttackModifier(Object* enemy) override;
};
