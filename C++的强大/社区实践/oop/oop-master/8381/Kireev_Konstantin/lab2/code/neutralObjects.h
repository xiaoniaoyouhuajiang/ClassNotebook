#ifndef NEUTRAL_OBJECTS_H
#define NEUTRAL_OBJECTS_H
#include "interfacesforobjects.h"
#include "neutralObjectsStrategy.h"

class BoostTower : public NeutralObjectInterface
{
public:
    QString getClass() override
    {
        return "BOOSTTOWER";
    }

    NeutralObjectInterface* copy() override
    {
        return new BoostTower();
    }

    void unitInfl(UnitInterface* unit) override
    {
        switch (unit->getType())
        {
            case DMG_ABS_INF:
            case CRT_DMG_INF:
                strategy = new BoostTowerInfantryStrategy();
                break;
            case DMG_ABS_CAV:
            case CRT_DMG_CAV:
                strategy = new BoostTowerCavalryStrategy();
                break;
            case DMG_ABS_ARC:
            case CRT_DMG_ARC:
                strategy = new BoostTowerArcherStrategy();
                break;
        }
        strategy->unitInfl(unit);
    }
};


class Village : public NeutralObjectInterface
{
public:
    QString getClass() override
    {
        return "VILLAGE";
    }

    NeutralObjectInterface* copy() override
    {
        return new Village();
    }

    void unitInfl(UnitInterface* unit) override
    {
        switch (unit->getType())
        {
            case DMG_ABS_INF:
            case CRT_DMG_INF:
                strategy = new VillageInfantryStrategy();
                break;
            case DMG_ABS_CAV:
            case CRT_DMG_CAV:
                strategy = new VillageCavalryStrategy();
                break;
            case DMG_ABS_ARC:
            case CRT_DMG_ARC:
                strategy = new VillageArcherStrategy();
                break;
        }
        strategy->unitInfl(unit);
    }
};


class ArmorHouse : public NeutralObjectInterface
{
public:
    QString getClass() override
    {
        return "ARMORHOUSE";
    }

    NeutralObjectInterface* copy() override
    {
        return new ArmorHouse();
    }

    void unitInfl(UnitInterface* unit) override
    {
        switch (unit->getType())
        {
            case DMG_ABS_INF:
            case CRT_DMG_INF:
                strategy = new ArmorHouseInfantryStrategy();
                break;
            case DMG_ABS_CAV:
            case CRT_DMG_CAV:
                strategy = new ArmorHouseCavalryStrategy();
                break;
            case DMG_ABS_ARC:
            case CRT_DMG_ARC:
                strategy = new ArmorHouseArcherStrategy();
                break;
        }
        strategy->unitInfl(unit);
    }
};


class GunSmith : public NeutralObjectInterface
{
public:
    QString getClass() override
    {
        return "GUNSMITH";
    }

    NeutralObjectInterface* copy() override
    {
        return new GunSmith();
    }

    void unitInfl(UnitInterface* unit) override
    {
        switch (unit->getType())
        {
            case DMG_ABS_INF:
            case CRT_DMG_INF:
                strategy = new SmithInfantryStrategy();
                break;
            case DMG_ABS_CAV:
            case CRT_DMG_CAV:
                strategy = new SmithCavalryStrategy();
                break;
            case DMG_ABS_ARC:
            case CRT_DMG_ARC:
                strategy = new SmithArcherStrategy();
                break;
        }
        strategy->unitInfl(unit);
    }
};

#endif // NEUTRAL_OBJECTS_H
