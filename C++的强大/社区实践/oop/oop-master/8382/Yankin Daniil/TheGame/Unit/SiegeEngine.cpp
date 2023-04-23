#include "SiegeEngine.h"
#include "Game/Game.h"
#include "Player/Player.h"
#include "Base/Base.h"
#include "Unit/UnitGroup.h"


SiegeEngine::SiegeEngine(Point point, Base* base) : Unit(point, base) {}
SiegeEngine::SiegeEngine(UnitSnapshot& snapshot, Base* base) : Unit(snapshot, base) {}
SiegeEngine::SiegeEngine(UnitSnapshot& snapshot, UnitGroup* group) : Unit(snapshot, group) {}

uint16_t SiegeEngine::getUnitClass() {
    return UNIT_SIEGE_ENGINE;
}

double SiegeEngine::classAttackModifier(Object* enemy) {
    if (enemy->getGroupType() == BASE)
        return 2;

    if (enemy->getGroupType() == UNIT) {
        auto unit = static_cast<IUnit*>(enemy);
        if (unit->getUnitClass() == UNIT_MELEE) {
            return 0.4;
        }

        if (unit->getUnitClass() == UNIT_RANGED) {
            return 0.4;
        }

        if (unit->getUnitClass() == UNIT_SIEGE_ENGINE) {
            return 1;
        }
    }
    return 0;
}



/* CATAPULT CATAPULT CATAPULT CATAPULT CATAPULT CATAPULT CATAPULT CATAPULT CATAPULT CATAPULT */

Catapult::Catapult(Point point, Base* base) : SiegeEngine(point, base) {
    strength = Strength(60, 2);
    armor = Armor(5);
    health = Health(100, 100);
    movePoints = MovePoints(2, 2);

    std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor()};
    Game::getInstance().getLogAdapter().log(LOG_PLOBJECT_CREATED, logParameters);
}

Catapult::Catapult(UnitSnapshot& snapshot, Base* base) : SiegeEngine(snapshot, base) {
    std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor()};
    Game::getInstance().getLogAdapter().log(LOG_PLOBJECT_CREATED, logParameters);
}

Catapult::Catapult(UnitSnapshot& snapshot, UnitGroup* group) : SiegeEngine(snapshot, group) {
    std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor()};
    Game::getInstance().getLogAdapter().log(LOG_PLOBJECT_CREATED, logParameters);
}

Catapult::~Catapult() {
    if (!isGroup) {
        std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor()};
        Game::getInstance().getLogAdapter().log(LOG_PLOBJECT_DESTRUCTED, logParameters);
    }
}

uint16_t Catapult::getObjectType() {
    return UNIT_CATAPULT;
}

double Catapult::typeAttackModifier(Object* enemy) {
    if (enemy->getGroupType() == BASE)
        return 1;

    if (enemy->getGroupType() == UNIT) {
        uint16_t enemyType = enemy->getObjectType();
        if (enemyType == UNIT_SWORDSMAN || enemyType == UNIT_PIKEMAN || enemyType == UNIT_CATAPULT || enemyType == UNIT_RAM)
            return 1.2;

        return 1;
    }
    return 0;
}



/* RAM RAM RAM RAM RAM RAM RAM RAM RAM RAM */

Ram::Ram(Point point, Base* base) : SiegeEngine(point, base) {
    strength = Strength(100, 0);
    armor = Armor(15);
    health = Health(100, 100);
    movePoints = MovePoints(2, 2);

    std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor()};
    Game::getInstance().getLogAdapter().log(LOG_PLOBJECT_CREATED, logParameters);
}

Ram::Ram(UnitSnapshot& snapshot, Base* base) : SiegeEngine(snapshot, base) {
    std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor()};
    Game::getInstance().getLogAdapter().log(LOG_PLOBJECT_CREATED, logParameters);
}

Ram::Ram(UnitSnapshot& snapshot, UnitGroup* group) : SiegeEngine(snapshot, group) {
    std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor()};
    Game::getInstance().getLogAdapter().log(LOG_PLOBJECT_CREATED, logParameters);
}

Ram::~Ram() {
    if (!isGroup) {
        std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor()};
        Game::getInstance().getLogAdapter().log(LOG_PLOBJECT_DESTRUCTED, logParameters);
    }
}

uint16_t Ram::getObjectType() {
    return UNIT_RAM;
}

double Ram::typeAttackModifier(Object* enemy) {
    if (enemy->getGroupType() == BASE)
        return 1;

    if (enemy->getGroupType() == UNIT) {
        uint16_t enemyType = enemy->getObjectType();
        if (enemyType == UNIT_CATAPULT || enemyType == UNIT_RAM)
            return 2;

        return 1;
    }
    return 0;
}
