#include "Ranged.h"
#include "Game/Game.h"
#include "Player/Player.h"
#include "Base/Base.h"
#include "Unit/UnitGroup.h"


Ranged::Ranged(Point point, Base* base) : Unit(point, base) {}
Ranged::Ranged(UnitSnapshot& snapshot, Base* base) : Unit(snapshot, base) {}
Ranged::Ranged(UnitSnapshot& snapshot, UnitGroup* group) : Unit(snapshot, group) {}

uint16_t Ranged::getUnitClass() {
    return UNIT_RANGED;
}

double Ranged::classAttackModifier(Object* enemy) {
    if (enemy->getGroupType() == BASE)
        return 0.3;

    if (enemy->getGroupType() == UNIT) {
        auto unit = static_cast<IUnit*>(enemy);
        if (unit->getUnitClass() == UNIT_MELEE) {
            return 1.4;
        }

        if (unit->getUnitClass() == UNIT_RANGED) {
            return 1;
        }

        if (unit->getUnitClass() == UNIT_SIEGE_ENGINE) {
            return 1;
        }
    }
    return 0;
}



/* ARCHER ARCHER ARCHER ARCHER ARCHER ARCHER ARCHER ARCHER ARCHER ARCHER */

Archer::Archer(Point point, Base* base) : Ranged(point, base) {
    strength = Strength(35, 2);
    armor = Armor(8);
    health = Health(100, 100);
    movePoints = MovePoints(2, 2);

    std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor()};
    Game::getInstance().getLogAdapter().log(LOG_PLOBJECT_CREATED, logParameters);
}

Archer::Archer(UnitSnapshot& snapshot, Base* base) : Ranged(snapshot, base) {
    std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor()};
    Game::getInstance().getLogAdapter().log(LOG_PLOBJECT_CREATED, logParameters);
}

Archer::Archer(UnitSnapshot& snapshot, UnitGroup* group) : Ranged(snapshot, group) {
    std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor()};
    Game::getInstance().getLogAdapter().log(LOG_PLOBJECT_CREATED, logParameters);
}

Archer::~Archer() {
    if (!isGroup) {
        std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor()};
        Game::getInstance().getLogAdapter().log(LOG_PLOBJECT_DESTRUCTED, logParameters);
    }
}

uint16_t Archer::getObjectType() {
    return UNIT_ARCHER;
}

double Archer::typeAttackModifier(Object* enemy) {
    if (enemy->getGroupType() == BASE)
        return 1;

    if (enemy->getGroupType() == UNIT) {
        uint16_t enemyType = enemy->getObjectType();
        if (enemyType == UNIT_SWORDSMAN || enemyType == UNIT_CROSSBOWMAN)
            return 1.2;

        auto unit = static_cast<IUnit*>(enemy);
        if (unit->getUnitClass() == UNIT_SIEGE_ENGINE)
            return 1.4;

        return 1;
    }
    return 0;
}



/* CROSSBOWMAN CROSSBOWMAN CROSSBOWMAN CROSSBOWMAN CROSSBOWMAN CROSSBOWMAN CROSSBOWMAN CROSSBOWMAN CROSSBOWMAN CROSSBOWMAN */

Crossbowman::Crossbowman(Point point, Base* base) : Ranged(point, base) {
    strength = Strength(45, 2);
    armor = Armor(8);
    health = Health(100, 100);
    movePoints = MovePoints(2, 2);

    std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor()};
    Game::getInstance().getLogAdapter().log(LOG_PLOBJECT_CREATED, logParameters);
}

Crossbowman::Crossbowman(UnitSnapshot& snapshot, Base* base) : Ranged(snapshot, base) {
    std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor()};
    Game::getInstance().getLogAdapter().log(LOG_PLOBJECT_CREATED, logParameters);
}

Crossbowman::Crossbowman(UnitSnapshot& snapshot, UnitGroup* group) : Ranged(snapshot, group) {
    std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor()};
    Game::getInstance().getLogAdapter().log(LOG_PLOBJECT_CREATED, logParameters);
}

Crossbowman::~Crossbowman() {
    if (!isGroup) {
        std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor()};
        Game::getInstance().getLogAdapter().log(LOG_PLOBJECT_DESTRUCTED, logParameters);
    }
}

uint16_t Crossbowman::getObjectType() {
    return UNIT_CROSSBOWMAN;
}

double Crossbowman::typeAttackModifier(Object* enemy) {
    if (enemy->getGroupType() == BASE)
        return 1;

    if (enemy->getGroupType() == UNIT) {
        uint16_t enemyType = enemy->getObjectType();
        if (enemyType == UNIT_SWORDSMAN || enemyType == UNIT_PIKEMAN)
            return 1.2;

        return 1;
    }
    return 0;
}



/* SCOUT_CAVALRY SCOUT_CAVALRY SCOUT_CAVALRY SCOUT_CAVALRY SCOUT_CAVALRY SCOUT_CAVALRY SCOUT_CAVALRY SCOUT_CAVALRY SCOUT_CAVALRY SCOUT_CAVALRY */

ScoutCavalry::ScoutCavalry(Point point, Base* base) : Ranged(point, base) {
    strength = Strength(25, 1);
    armor = Armor(6);
    health = Health(100, 100);
    movePoints = MovePoints(6, 6);

    std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor()};
    Game::getInstance().getLogAdapter().log(LOG_PLOBJECT_CREATED, logParameters);
}

ScoutCavalry::ScoutCavalry(UnitSnapshot& snapshot, Base* base) : Ranged(snapshot, base) {
    std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor()};
    Game::getInstance().getLogAdapter().log(LOG_PLOBJECT_CREATED, logParameters);
}

ScoutCavalry::ScoutCavalry(UnitSnapshot& snapshot, UnitGroup* group) : Ranged(snapshot, group) {
    std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor()};
    Game::getInstance().getLogAdapter().log(LOG_PLOBJECT_CREATED, logParameters);
}

ScoutCavalry::~ScoutCavalry() {
    if (!isGroup) {
        std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor()};
        Game::getInstance().getLogAdapter().log(LOG_PLOBJECT_DESTRUCTED, logParameters);
    }
}

uint16_t ScoutCavalry::getObjectType() {
    return UNIT_SCOUT_CAVALRY;
}

double ScoutCavalry::typeAttackModifier(Object* enemy) {
    if (enemy->getGroupType() == BASE)
        return 1;

    if (enemy->getGroupType() == UNIT) {
        uint16_t enemyType = enemy->getObjectType();
        if (enemyType == UNIT_ARCHER || enemyType == UNIT_CROSSBOWMAN)
            return 1.2;

        return 1;
    }
    return 0;
}
