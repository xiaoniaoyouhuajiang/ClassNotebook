#include "Unit.h"
#include "Game/Game.h"
#include "Field/Field.h"
#include "Player/Player.h"
#include "Base/Base.h"
#include <math.h>


Unit::Unit(Point point, Base* base) : point(point), base(base), isGroup(false), attacked(false) {
    base->addUnit(this);
}

Unit::Unit(UnitSnapshot& snapshot, Base* base) : point(snapshot.point), base(base), isGroup(false), health(snapshot.health),
    strength(snapshot.strength), armor(snapshot.armor), movePoints(snapshot.movePoints), attacked(snapshot.attacked) {
    base->addUnit(this);
}

Unit::Unit(UnitSnapshot& snapshot, UnitGroup* group) : point(snapshot.point), group(group), isGroup(true), health(snapshot.health),
    strength(snapshot.strength), armor(snapshot.armor), movePoints(snapshot.movePoints), attacked(snapshot.attacked) {}

Unit::~Unit() {
    if (!isGroup) {
        base->removeUnit(this);
        Game::getInstance().objectWasDestructed(static_cast <Object*> (this));
    }
}



Point Unit::getPoint() {
    return point;
}

void Unit::setPoint(Point point) {
    this->point = point;
}

Player* Unit::getPlayer() {
    return base->getPlayer();
}

Base* Unit::getBase() {
    return base;
}



uint16_t Unit::getMaxHealth() {
    return health.getMaxHealth();
}

uint16_t Unit::getHealth() {
    return health.getHealth();
}

uint16_t Unit::getAttack() {
    return strength.getStrength();
}

uint16_t Unit::getAttackRadius() {
    return strength.getRadius();
}

uint16_t Unit::getArmor() {
    return armor.getArmor();
}

uint16_t Unit::getMaxMovePoints() {
    return movePoints.getMaxMovePoints();
}

uint16_t Unit::getMovePoints() {
    return movePoints.getMovePoints();
}

void Unit::setMovePoints(uint16_t points) {
    movePoints.setMovePoints(points);
}



uint16_t Unit::giveDamage(IUnit* enemy) {
    return strength.getStrength() * classAttackModifier(enemy) * typeAttackModifier(enemy);
}

uint16_t Unit::giveDamage(Base* enemy) {
    return strength.getStrength() * classAttackModifier(enemy) * typeAttackModifier(enemy);
}

bool Unit::takeDamage(uint16_t damage) {
    uint16_t initHealth = getHealth();
    damage = std::max(2, static_cast<int>(damage - armor.getArmor() * 0.2));

    health.setHealth(std::max(health.getHealth() - damage, 0));

    if (!isGroup) {
        uint16_t takenDamage = initHealth - health.getHealth();
        std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor(), takenDamage};
        Game::getInstance().getLogAdapter().log(LOG_TAKE_DAMAGE, logParameters);
    }

    if (health.getHealth() == 0) {
        if (!isGroup) {
            delete this;
        }
        return false;
    }
    return true;

    // Выжил - true, помер - false
    // Если единичный, то при помирании самоуничтожается
    // Если в составе группы, то за уничтожение отвечает группа
}

void Unit::setAttacked() {
    attacked = true;
}

void Unit::unsetAttacked() {
    attacked = false;
}

bool Unit::checkAttacked() {
    return attacked;
}



void Unit::smallHeal(uint16_t healSize) {
    int initHealth = health.getHealth();
    health.setHealth(std::min(static_cast <uint16_t> (health.getHealth() + healSize), health.getMaxHealth()));
    if (!isGroup) {
        std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor(), health.getHealth() - initHealth};
        Game::getInstance().getLogAdapter().log(LOG_NEUT_SMALL_HEAL, logParameters);
    }
}

void Unit::fullHeal() {
    health.setHealth(health.getMaxHealth());
    if (!isGroup) {
        std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor()};
        Game::getInstance().getLogAdapter().log(LOG_NEUT_FULL_HEAL, logParameters);
    }
}

void Unit::attackModification(int16_t modSize) {
    if (modSize < 0) {
        strength.setStrength(std::max(strength.getStrength() + modSize, 0));
        if (!isGroup) {
            std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor(), modSize};
            Game::getInstance().getLogAdapter().log(LOG_NEUT_ATT_MOD, logParameters);
        }
        return;
    }
    strength.setStrength(strength.getStrength() + modSize);
    if (!isGroup) {
        std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor(), modSize};
        Game::getInstance().getLogAdapter().log(LOG_NEUT_ATT_MOD, logParameters);
    }
}

void Unit::armorModification(int16_t modSize) {
    if (modSize < 0) {
        armor.setArmor(std::max(armor.getArmor() + modSize, 0));
        if (!isGroup) {
            std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor(), modSize};
            Game::getInstance().getLogAdapter().log(LOG_NEUT_ARM_MOD, logParameters);
        }
        return;
    }
    armor.setArmor(armor.getArmor() + modSize);
    if (!isGroup) {
        std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor(), modSize};
        Game::getInstance().getLogAdapter().log(LOG_NEUT_ARM_MOD, logParameters);
    }
}

void Unit::renewMovePoints() {
    movePoints.setMovePoints(movePoints.getMaxMovePoints());

    if (!isGroup) {
        std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY(), getPlayer()->getColor()};
        Game::getInstance().getLogAdapter().log(LOG_NEUT_REN_MOV, logParameters);
    }
}


uint16_t Unit::generateUnitType() {
    auto typeCount = UNIT_RAM - UNIT;
    auto unitType = rand() % typeCount + UNIT_SWORDSMAN;
    return unitType;
}
