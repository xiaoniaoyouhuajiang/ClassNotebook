#ifndef NEUTRAL_OBJECTS_H
#define NEUTRAL_OBJECTS_H
#include "creatures_basic_interfaces.h"
#include "neutral_objects_effects_strategies.h"


class Banner : public INeutralObject
{
public:
    QString getClass() override { return "Banner"; }

    INeutralObject* copy() override { return new Banner(); }

    NeutralObjectType getType() override { return BANNER; }

    void influenceOnUnit(IUnit* unit) override{
        switch (unit->getType()) {
            case ABSORB_INFANTRY:
            case CRIT_INFANTRY:
                strategy = new BannerInfantryStrategy();
                break;
            case ABSORB_CAVALRY:
            case CRIT_CAVALRY:
                strategy = new BannerCavalryStrategy();
                break;
            case ABSORB_ARCHER:
            case CRIT_ARCHER:
                strategy = new BannerArcherStrategy();
                break;
        }

        strategy->influenceOnUnit(unit);
    }
};


class Tower : public INeutralObject
{
public:
    QString getClass() override { return "Tower"; }

    INeutralObject* copy() override { return new Tower(); }

    NeutralObjectType getType() override { return TOWER; }

    void influenceOnUnit(IUnit* unit) override{
        switch (unit->getType()) {
            case ABSORB_INFANTRY:
            case CRIT_INFANTRY:
                strategy = new TowerInfantryStrategy();
                break;
            case ABSORB_CAVALRY:
            case CRIT_CAVALRY:
                strategy = new TowerCavalryStrategy();
                break;
            case ABSORB_ARCHER:
            case CRIT_ARCHER:
                strategy = new TowerArcherStrategy();
                break;
        }

        strategy->influenceOnUnit(unit);
    }
};


class Temple : public INeutralObject
{
public:
    QString getClass() override { return "Temple"; }

    INeutralObject* copy() override { return new Temple(); }

    NeutralObjectType getType() override { return TEMPLE; }

    void influenceOnUnit(IUnit* unit) override{
        switch (unit->getType()) {
            case ABSORB_INFANTRY:
            case CRIT_INFANTRY:
                strategy = new TempleInfantryStrategy();
                break;
            case ABSORB_CAVALRY:
            case CRIT_CAVALRY:
                strategy = new TempleCavalryStrategy();
                break;
            case ABSORB_ARCHER:
            case CRIT_ARCHER:
                strategy = new TempleArcherStrategy();
                break;
        }

        strategy->influenceOnUnit(unit);
    }
};

class Forge : public INeutralObject
{
public:
    QString getClass() override { return "Forge"; }

    INeutralObject* copy() override { return new Forge(); }

    NeutralObjectType getType() override { return FORGE; }

    void influenceOnUnit(IUnit* unit) override{
        switch (unit->getType()) {
            case ABSORB_INFANTRY:
            case CRIT_INFANTRY:
                strategy = new ForgeInfantryStrategy();
                break;
            case ABSORB_CAVALRY:
            case CRIT_CAVALRY:
                strategy = new ForgeCavalryStrategy();
                break;
            case ABSORB_ARCHER:
            case CRIT_ARCHER:
                strategy = new ForgeArcherStrategy();
                break;
        }

        strategy->influenceOnUnit(unit);
    }
};


#endif // NEUTRAL_OBJECTS_H
