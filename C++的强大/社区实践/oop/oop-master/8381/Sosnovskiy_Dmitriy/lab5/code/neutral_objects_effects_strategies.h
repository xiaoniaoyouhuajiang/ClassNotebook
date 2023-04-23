#ifndef NEUTRAL_OBJECTS_EFFECTS_STRATEGIES_H
#define NEUTRAL_OBJECTS_EFFECTS_STRATEGIES_H
#include "creatures_basic_interfaces.h"

class INeutralObjectsEffectStrategy
{
public:
    virtual ~INeutralObjectsEffectStrategy() = default;
    virtual void influenceOnUnit(IUnit* unit) const = 0;
};


//banner object strategies
class BannerInfantryStrategy : public INeutralObjectsEffectStrategy
{
public:
    void influenceOnUnit(IUnit* unit) const override {
        unit->getDamage()->setBonus(10);
    }
};


class BannerCavalryStrategy : public INeutralObjectsEffectStrategy
{
public:
    void influenceOnUnit(IUnit* unit) const override {
        unit->getDamage()->setBonus(5);
    }
};


class BannerArcherStrategy : public INeutralObjectsEffectStrategy
{
public:
    void influenceOnUnit(IUnit* unit) const override {
        unit->getDamage()->setBonus(10);
    }
};

//tower object strategies
class TowerInfantryStrategy : public INeutralObjectsEffectStrategy
{
public:
    void influenceOnUnit(IUnit* unit) const override {
        unit->getArmor()->setBonus(2);
    }
};


class TowerCavalryStrategy : public INeutralObjectsEffectStrategy
{
public:
    void influenceOnUnit(IUnit* unit) const override {
        unit->getArmor()->setBonus(2);
    }
};

class TowerArcherStrategy : public INeutralObjectsEffectStrategy
{
public:
    void influenceOnUnit(IUnit* unit) const override {
        unit->getArmor()->setBonus(2);
    }
};


//temple object strategies
class TempleInfantryStrategy : public INeutralObjectsEffectStrategy
{
public:
    void influenceOnUnit(IUnit* unit) const override {
        unit->setHealth(unit->getHealth().getValue() + 10);
    }
};

class TempleCavalryStrategy : public INeutralObjectsEffectStrategy
{
public:
    void influenceOnUnit(IUnit* unit) const override {
        unit->setHealth(unit->getHealth().getValue() + 10);
    }
};

class TempleArcherStrategy : public INeutralObjectsEffectStrategy
{
public:
    void influenceOnUnit(IUnit* unit) const override {
        unit->setHealth(unit->getHealth().getValue() + 10);
    }
};

//forge object strategies
class ForgeInfantryStrategy : public INeutralObjectsEffectStrategy
{
public:
    void influenceOnUnit(IUnit* unit) const override {
        unit->getArmor()->setBonus(1);
        unit->getDamage()->setBonus(10);
    }
};

class ForgeCavalryStrategy : public INeutralObjectsEffectStrategy
{
public:
    void influenceOnUnit(IUnit* unit) const override {
        unit->getArmor()->setBonus(1);
        unit->getDamage()->setBonus(10);
    }
};

class ForgeArcherStrategy : public INeutralObjectsEffectStrategy
{
public:
    void influenceOnUnit(IUnit* unit) const override {
        unit->getArmor()->setBonus(1);
        unit->getDamage()->setBonus(10);
    }
};
#endif // NEUTRAL_OBJECTS_EFFECTS_STRATEGIES_H
