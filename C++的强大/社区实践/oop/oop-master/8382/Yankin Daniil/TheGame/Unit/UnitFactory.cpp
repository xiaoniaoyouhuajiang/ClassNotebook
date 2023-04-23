#include "UnitFactory.h"
#include "Melee.h"
#include "Ranged.h"
#include "SiegeEngine.h"


Unit* UnitFactory::produce(uint16_t unitType, Point point, Base* base) {
    Unit* unit;
    switch(unitType) {
    case UNIT_SWORDSMAN:
        unit = new Swordsman(point, base);
        break;
    case UNIT_PIKEMAN:
        unit = new Pikeman(point, base);
        break;
    case UNIT_SHOCK_CAVALRY:
        unit = new ShockCavalry(point, base);
        break;
    case UNIT_ARCHER:
        unit = new Archer(point, base);
        break;
    case UNIT_CROSSBOWMAN:
        unit = new Crossbowman(point, base);
        break;
    case UNIT_SCOUT_CAVALRY:
        unit = new ScoutCavalry(point, base);
        break;
    case UNIT_CATAPULT:
        unit = new Catapult(point, base);
        break;
    case UNIT_RAM:
        unit = new Ram(point, base);
        break;
    }
    return unit;
}

Unit* UnitFactory::produce(Unit::UnitSnapshot& snapshot, Base* base) {
    Unit* unit;
    switch(snapshot.getObjectType()) {
    case UNIT_SWORDSMAN:
        unit = new Swordsman(snapshot, base);
        break;
    case UNIT_PIKEMAN:
        unit = new Pikeman(snapshot, base);
        break;
    case UNIT_SHOCK_CAVALRY:
        unit = new ShockCavalry(snapshot, base);
        break;
    case UNIT_ARCHER:
        unit = new Archer(snapshot, base);
        break;
    case UNIT_CROSSBOWMAN:
        unit = new Crossbowman(snapshot, base);
        break;
    case UNIT_SCOUT_CAVALRY:
        unit = new ScoutCavalry(snapshot, base);
        break;
    case UNIT_CATAPULT:
        unit = new Catapult(snapshot, base);
        break;
    case UNIT_RAM:
        unit = new Ram(snapshot, base);
        break;
    }
    return unit;
}

Unit* UnitFactory::produce(Unit::UnitSnapshot& snapshot, UnitGroup* group) {
    Unit* unit;
    switch(snapshot.getObjectType()) {
    case UNIT_SWORDSMAN:
        unit = new Swordsman(snapshot, group);
        break;
    case UNIT_PIKEMAN:
        unit = new Pikeman(snapshot, group);
        break;
    case UNIT_SHOCK_CAVALRY:
        unit = new ShockCavalry(snapshot, group);
        break;
    case UNIT_ARCHER:
        unit = new Archer(snapshot, group);
        break;
    case UNIT_CROSSBOWMAN:
        unit = new Crossbowman(snapshot, group);
        break;
    case UNIT_SCOUT_CAVALRY:
        unit = new ScoutCavalry(snapshot, group);
        break;
    case UNIT_CATAPULT:
        unit = new Catapult(snapshot, group);
        break;
    case UNIT_RAM:
        unit = new Ram(snapshot, group);
        break;
    }
    return unit;
}
