#pragma once

#include "Unit.h"


class SiegeEngine : public Unit
{
public:
    SiegeEngine(Point point, Base* base);
    SiegeEngine(UnitSnapshot& snapshot, Base* base);
    SiegeEngine(UnitSnapshot& snapshot, UnitGroup* group);
    uint16_t getUnitClass() override;
    double classAttackModifier(Object* enemy) override;
};



class Catapult : public SiegeEngine
{
public:
    Catapult(Point point, Base* base);
    Catapult(UnitSnapshot& snapshot, Base* base);
    Catapult(UnitSnapshot& snapshot, UnitGroup* group);
    ~Catapult();
    uint16_t getObjectType() override;
    double typeAttackModifier(Object* enemy) override;
};


class Ram : public SiegeEngine
{
public:
    Ram(Point point, Base* base);
    Ram(UnitSnapshot& snapshot, Base* base);
    Ram(UnitSnapshot& snapshot, UnitGroup* group);
    ~Ram();
    uint16_t getObjectType() override;
    double typeAttackModifier(Object* enemy) override;
};
