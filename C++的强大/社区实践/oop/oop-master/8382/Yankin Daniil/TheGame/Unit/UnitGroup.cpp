#include "UnitGroup.h"
#include "Game/Game.h"
#include "Landscape/LandscapeHeader.h"
#include "Player/Player.h"
#include "Base/Base.h"


UnitGroup::UnitGroup(std::vector <Unit*> details) : maxGroupSize(MAX_GROUP_SIZE) {
    if (details.size() == 0)
        return;

    base = details.back()->getBase();
    uint16_t unitType = details.back()->getObjectType();
    uint16_t minMovePoints = details.back()->getMovePoints();
    Point point = details.back()->getPoint();

    while (unitSet.size() < maxGroupSize && details.size() > 0) {
        Unit* unit = details.back();
        details.pop_back();
        if (unit->getObjectType() != unitType)
            continue;

        minMovePoints = std::min(minMovePoints, unit->getMovePoints());
        unit->isGroup = true;
        unit->group = this;

        base->removeUnit(unit);
        Game::getInstance().objectWasDestructed(unit);

        unitSet.insert(unit);
    }

    setMovePoints(minMovePoints);
    setPoint(point);
    base->addUnit(this);
    Game::getInstance().objectWasCreated(static_cast <Object*> (this));
}

UnitGroup::UnitGroup(UnitGroupSnapshot& snapshot, Base* base) : maxGroupSize(MAX_GROUP_SIZE), base(base) {
    for (auto unitSnapshot = snapshot.unitSnapVector.begin(); unitSnapshot != snapshot.unitSnapVector.end(); unitSnapshot++) {
        UnitFactory factory;
        auto unit = factory.produce(*unitSnapshot, this);
        unitSet.insert(unit);
    }
    base->addUnit(this);
    std::vector<int> logParameters = {getObjectType(), getPoint().getX(), getPoint().getY(), getPlayer()->getColor()};
    Game::getInstance().getLogAdapter().log(LOG_PLOBJECT_CREATED, logParameters);
}

UnitGroup::~UnitGroup() {
    std::vector<int> logParameters = {getObjectType(), getPoint().getX(), getPoint().getY(), getPlayer()->getColor()};

    Game::getInstance().objectWasDestructed(static_cast <Object*> (this));
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit = unitSet.begin()) {
        delete *unit;
        unitSet.erase(unit);
    }
    base->removeUnit(this);

    Game::getInstance().getLogAdapter().log(LOG_PLOBJECT_DESTRUCTED, logParameters);
}



uint16_t UnitGroup::getUnitClass() {
    auto unit = unitSet.begin();
    return (*unit)->getUnitClass();
}

uint16_t UnitGroup::getObjectType() {
    auto unit = unitSet.begin();
    return (*unit)->getObjectType();
}



Point UnitGroup::getPoint() {
    auto unit = unitSet.begin();
    return (*unit)->getPoint();
}

void UnitGroup::setPoint(Point point) {
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++) {
       (*unit)->setPoint(point);
    }
}

Player* UnitGroup::getPlayer() {
    return base->getPlayer();
}

Base* UnitGroup::getBase() {
    return base;
}



uint16_t UnitGroup::getMaxHealth() {
    uint16_t maxHealthSum = 0;
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++) {
        maxHealthSum += (*unit)->getMaxHealth();
    }
    return maxHealthSum;
}

uint16_t UnitGroup::getHealth() {
    uint16_t healthSum = 0;
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++) {
        healthSum += (*unit)->getHealth();
    }
    return healthSum;
}

uint16_t UnitGroup::getAttack() {
    uint16_t strengthSum = 0;
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++) {
        strengthSum += (*unit)->getAttack();
    }
    return strengthSum * 0.85;
}

uint16_t UnitGroup::getAttackRadius() {
    auto unit = unitSet.begin();
    return (*unit)->getAttackRadius();
}

uint16_t UnitGroup::getArmor() {
    uint16_t armorSum = 0;
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++) {
        armorSum += (*unit)->getArmor();
    }
    return armorSum * 0.85;
}

uint16_t UnitGroup::getMaxMovePoints() {
    uint16_t maxMovePoints = 0;
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++) {
        if ((*unit)->getMaxMovePoints() < maxMovePoints || maxMovePoints == 0) {
            maxMovePoints = (*unit)->getMaxMovePoints();
        }
    }
    return maxMovePoints;
}

uint16_t UnitGroup::getMovePoints() {
    uint16_t maxMovePoints = getMaxMovePoints();

    uint16_t movePoints = 0;
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++) {
        if ((*unit)->getMovePoints() > movePoints) {
            movePoints = (*unit)->getMovePoints();
        }
    }
    return std::min(movePoints, maxMovePoints);
}

void UnitGroup::setMovePoints(uint16_t points) {
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++) {
        (*unit)->setMovePoints(points);
    }
}



uint16_t UnitGroup::giveDamage(IUnit* enemy) {
    uint16_t damage = 0;
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++) {
        damage += (*unit)->giveDamage(enemy);
    }
    return damage;
}

uint16_t UnitGroup::giveDamage(Base* enemy) {
    uint16_t damage = 0;
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++) {
        damage += (*unit)->giveDamage(enemy);
    }
    return damage;
}

bool UnitGroup::takeDamage(uint16_t damage) {
    damage /= unitSet.size();
    std::vector <Unit*> diedUnits;

    uint16_t initHealth = getHealth();

    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++) {
        bool alive = (*unit)->takeDamage(damage);
        if (!alive)
            diedUnits.push_back(*unit);
    }

    uint16_t takenDamage = initHealth - getHealth();
    std::vector<int> logParameters = {getObjectType(), getPoint().getX(), getPoint().getY(), getPlayer()->getColor(), takenDamage};
    Game::getInstance().getLogAdapter().log(LOG_TAKE_DAMAGE, logParameters);

    for (uint16_t i = 0; i < diedUnits.size() && unitSet.size() > 1; i++) {
        unitSet.erase(diedUnits[i]);
    }

    if (unitSet.size() == 1 && getHealth() == 0) {
        delete this;
        return false;
    }
    return true;
}



void UnitGroup::join(Unit* unit, bool moveTo) {
    if (unitSet.size() > maxGroupSize && unit->getObjectType() != getObjectType())
        return;

    Game::getInstance().objectWasDestructed(unit);
    base->removeUnit(unit);

    if (moveTo) {
        move(unit->point);
    }
    else {
        unit->setMovePoints(unit->getMovePoints() - Game::getInstance().getGameMediator().getLandscape(getPoint())->getMovementCost());
    }

    unit->isGroup = true;
    unit->group = this;
    unit->point = getPoint();

    uint16_t minMovePoints = std::min(getMovePoints(), unit->getMovePoints());

    unitSet.insert(unit);

    setMovePoints(minMovePoints);
}

void UnitGroup::join(UnitGroup* group, bool moveTo) {
    if (unitSet.size() + group->getGroupSize() > maxGroupSize && group->getObjectType() != getObjectType())
        return;

    Game::getInstance().objectWasDestructed(group);
    base->removeUnit(group);

    if (moveTo) {
        move(group->getPoint());
    }
    else {
        group->setMovePoints(getMovePoints() - Game::getInstance().getGameMediator().getLandscape(getPoint())->getMovementCost());
    }

    uint16_t minMovePoints = std::min(getMovePoints(), group->getMovePoints());

    for (auto unit = group->unitSet.begin(); unit != group->unitSet.end(); unit++) {
        (*unit)->group = this;
        unitSet.insert(*unit);
    }

    setMovePoints(minMovePoints);
    group->unitSet.clear();
    delete group;
}



uint16_t UnitGroup::getMaxGroupSize() {
    return maxGroupSize;
}

uint16_t UnitGroup::getGroupSize() {
    return unitSet.size();
}



void UnitGroup::smallHeal(uint16_t healSize) {
    int initHealth = getHealth();
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++)
        (*unit)->smallHeal(healSize);

    std::vector<int> logParameters = {getObjectType(), getPoint().getX(), getPoint().getY(), getPlayer()->getColor(), getHealth() - initHealth};
    Game::getInstance().getLogAdapter().log(LOG_NEUT_SMALL_HEAL, logParameters);
}

void UnitGroup::fullHeal() {
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++)
        (*unit)->fullHeal();

    std::vector<int> logParameters = {getObjectType(), getPoint().getX(), getPoint().getY(), getPlayer()->getColor()};
    Game::getInstance().getLogAdapter().log(LOG_NEUT_FULL_HEAL, logParameters);
}

void UnitGroup::attackModification(int16_t modSize) {
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++)
        (*unit)->attackModification(modSize);

    std::vector<int> logParameters = {getObjectType(), getPoint().getX(), getPoint().getY(), getPlayer()->getColor(), modSize};
    Game::getInstance().getLogAdapter().log(LOG_NEUT_ATT_MOD, logParameters);
}

void UnitGroup::armorModification(int16_t modSize) {
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++)
        (*unit)->armorModification(modSize);

    std::vector<int> logParameters = {getObjectType(), getPoint().getX(), getPoint().getY(), getPlayer()->getColor(), modSize};
    Game::getInstance().getLogAdapter().log(LOG_NEUT_ARM_MOD, logParameters);
}

void UnitGroup::renewMovePoints() {
    for (auto unit = unitSet.begin(); unit != unitSet.end(); unit++)
        (*unit)->renewMovePoints();

    std::vector<int> logParameters = {getObjectType(), getPoint().getX(), getPoint().getY(), getPlayer()->getColor()};
    Game::getInstance().getLogAdapter().log(LOG_NEUT_REN_MOV, logParameters);
}


void UnitGroup::setAttacked() {
    for (auto unit : unitSet) {
        unit->attacked = true;
    }
}

void UnitGroup::unsetAttacked() {
    for (auto unit : unitSet) {
        unit->attacked = false;
    }
}

bool UnitGroup::checkAttacked() {
    for (auto unit : unitSet) {
        if (unit->checkAttacked()) {
            return true;
        }
    }
    return false;
}
