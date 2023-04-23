#ifndef NEUTRAL_OBJECTS_EFFECTS_STRATEGIES_H
#define NEUTRAL_OBJECTS_EFFECTS_STRATEGIES_H
#include "interfacesforobjects.h"

class NeutralObjectsEffectStrategyInterface
{
public:
    virtual ~NeutralObjectsEffectStrategyInterface() = default;
    virtual void influenceOnUnit(UnitInterface* unit) const = 0;
};




class VillageInfantryStrategy : public NeutralObjectsEffectStrategyInterface
{
public:
    void influenceOnUnit(UnitInterface* unit) const override
    {
        unit->getDamage()->setBonus(3);
        unit->getArmor()->setBonus(3);
        unit->setHealth(unit->getHealth().getValue() + 3);
    }
};


class VillageCavalryStrategy : public NeutralObjectsEffectStrategyInterface
{
public:
    void influenceOnUnit(UnitInterface* unit) const override
    {
        unit->getDamage()->setBonus(3);
        unit->getArmor()->setBonus(3);
        unit->setHealth(unit->getHealth().getValue() + 3);
    }
};


class VillageArcherStrategy : public NeutralObjectsEffectStrategyInterface
{
public:
    void influenceOnUnit(UnitInterface* unit) const override
    {
        unit->getDamage()->setBonus(3);
        unit->getArmor()->setBonus(3);
        unit->setHealth(unit->getHealth().getValue() + 3);
    }
};




class BoostTowerInfantryStrategy : public NeutralObjectsEffectStrategyInterface
{
public:
    void influenceOnUnit(UnitInterface* unit) const override
    {
        unit->getDamage()->setBonus(15);
    }
};


class BoostTowerCavalryStrategy : public NeutralObjectsEffectStrategyInterface
{
public:
    void influenceOnUnit(UnitInterface* unit) const override
    {
        unit->getDamage()->setBonus(15);
    }
};

class BoostTowerArcherStrategy : public NeutralObjectsEffectStrategyInterface
{
public:
    void influenceOnUnit(UnitInterface* unit) const override
    {
        unit->getDamage()->setBonus(15);
    }
};





class ArmorHouseInfantryStrategy : public NeutralObjectsEffectStrategyInterface
{
public:
    void influenceOnUnit(UnitInterface* unit) const override
    {
        unit->getArmor()->setBonus(10);
    }
};

class ArmorHouseCavalryStrategy : public NeutralObjectsEffectStrategyInterface
{
public:
    void influenceOnUnit(UnitInterface* unit) const override
    {
        unit->getArmor()->setBonus(10);
    }
};

class ArmorHouseArcherStrategy : public NeutralObjectsEffectStrategyInterface
{
public:
    void influenceOnUnit(UnitInterface* unit) const override
    {
        unit->getArmor()->setBonus(10);
    }
};




class SmithInfantryStrategy : public NeutralObjectsEffectStrategyInterface
{
public:
    void influenceOnUnit(UnitInterface* unit) const override
    {
        unit->getArmor()->setBonus(2);
        unit->getDamage()->setBonus(5);
    }
};

class SmithCavalryStrategy : public NeutralObjectsEffectStrategyInterface
{
public:
    void influenceOnUnit(UnitInterface* unit) const override
    {
        unit->getArmor()->setBonus(2);
        unit->getDamage()->setBonus(5);
    }
};

class SmithArcherStrategy : public NeutralObjectsEffectStrategyInterface
{
public:
    void influenceOnUnit(UnitInterface* unit) const override
    {
        unit->getArmor()->setBonus(2);
        unit->getDamage()->setBonus(5);
    }
};


#endif // NEUTRAL_OBJECTS_EFFECTS_STRATEGIES_H
