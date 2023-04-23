#ifndef NEUTRAL_OBJECTS_H
#define NEUTRAL_OBJECTS_H
#include "interfacesforobjects.h"
#include "neutralObjectsStrategy.h"


class ArmorHouse : public NeutralObjectInterface
{
public:
    QString getClass() override { return "ArmorHouse"; }

    NeutralObjectInterface* copy() override { return new ArmorHouse(); }

    NeutralObjectType getType() override { return ARMORHOUSE; }

    void influenceOnUnit(UnitInterface* unit) override
    {
        switch (unit->getType()) {
            case ABSORB_INFANTRY:
            case CRIT_INFANTRY:
                strategy = new ArmorHouseInfantryStrategy();
                break;
            case ABSORB_CAVALRY:
            case CRIT_CAVALRY:
                strategy = new ArmorHouseCavalryStrategy();
                break;
            case ABSORB_ARCHER:
            case CRIT_ARCHER:
                strategy = new ArmorHouseArcherStrategy();
                break;
        }

        strategy->influenceOnUnit(unit);
    }
};


class BoostTower : public NeutralObjectInterface
{
public:
    QString getClass() override { return "BoostTower"; }

    NeutralObjectInterface* copy() override { return new BoostTower(); }

    NeutralObjectType getType() override { return BOOSTTOWER; }

    void influenceOnUnit(UnitInterface* unit) override{
        switch (unit->getType()) {
            case ABSORB_INFANTRY:
            case CRIT_INFANTRY:
                strategy = new BoostTowerInfantryStrategy();
                break;
            case ABSORB_CAVALRY:
            case CRIT_CAVALRY:
                strategy = new BoostTowerCavalryStrategy();
                break;
            case ABSORB_ARCHER:
            case CRIT_ARCHER:
                strategy = new BoostTowerArcherStrategy();
                break;
        }

        strategy->influenceOnUnit(unit);
    }
};


class Village : public NeutralObjectInterface
{
public:
    QString getClass() override { return "Village"; }

    NeutralObjectInterface* copy() override { return new Village(); }

    NeutralObjectType getType() override { return VILLAGE; }

    void influenceOnUnit(UnitInterface* unit) override{
        switch (unit->getType()) {
            case ABSORB_INFANTRY:
            case CRIT_INFANTRY:
                strategy = new VillageInfantryStrategy();
                break;
            case ABSORB_CAVALRY:
            case CRIT_CAVALRY:
                strategy = new VillageCavalryStrategy();
                break;
            case ABSORB_ARCHER:
            case CRIT_ARCHER:
                strategy = new VillageArcherStrategy();
                break;
        }

        strategy->influenceOnUnit(unit);
    }
};

class GunSmith : public NeutralObjectInterface
{
public:
    QString getClass() override { return "GunSmith"; }

    NeutralObjectInterface* copy() override { return new GunSmith(); }

    NeutralObjectType getType() override { return GUNSMITH; }

    void influenceOnUnit(UnitInterface* unit) override{
        switch (unit->getType()) {
            case ABSORB_INFANTRY:
            case CRIT_INFANTRY:
                strategy = new SmithInfantryStrategy();
                break;
            case ABSORB_CAVALRY:
            case CRIT_CAVALRY:
                strategy = new SmithCavalryStrategy();
                break;
            case ABSORB_ARCHER:
            case CRIT_ARCHER:
                strategy = new SmithArcherStrategy();
                break;
        }

        strategy->influenceOnUnit(unit);
    }
};


#endif // NEUTRAL_OBJECTS_H
