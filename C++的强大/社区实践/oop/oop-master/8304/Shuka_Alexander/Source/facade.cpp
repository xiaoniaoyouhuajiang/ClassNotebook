#include "facade.h"


Facade::Facade(std::shared_ptr<Mediator> mediator,
               std::shared_ptr<unit::Base> base,
               std::shared_ptr<std::set<std::shared_ptr<unit::Unit>>> units,
               std::shared_ptr<unit::Base> enemyBase,
               std::shared_ptr<GameField> field,
               std::shared_ptr<Logger> logger)
{
    this->base = base;
    this->mediator = mediator;
    this->units = units;
    this->enemyBase = enemyBase;
    this->field = field;
    this->logger = logger;
}


void Facade::charge()
{
    for (auto unit : *units) {
        if (!attack(unit)) {
            moveUnit(unit);
        }
    }
}


void Facade::deffend()
{
    for (auto unit : *units) {
        attack(unit);
    }
}


bool Facade::createGroundUnit()
{
    auto posEnemy = enemyBase->getPosition();
    auto posBase = base->getPosition();
    srand(time(0));

    int dx = 0;
    int dy = 0;
    auto choose = rand() % 3;

    switch (choose) {
    case 1:
        dy++;
        break;
    case 2:
        dy--;
        break;
    }

    if (posBase.x < posEnemy.x) {
        dx++;
    }
    else {
        dx--;
    }

    auto unit = base->createGroundUnit(dx, dy);
    if (unit) {
        units->insert(unit);
        field->addUnit(unit);
        return true;
    }

    return false;
}


bool Facade::createStandingUnit()
{
    auto posEnemy = enemyBase->getPosition();
    auto posBase = base->getPosition();
    srand(time(0));

    int dx = 0;
    int dy = 0;
    auto choose = rand() % 3;

    switch (choose) {
    case 1:
        dy++;
        break;
    case 2:
        dy--;
        break;
    }

    if (posBase.x < posEnemy.x) {
        dx++;
    }
    else {
        dx--;
    }

    auto unit = base->createStandingUnit(dx, dy);
    if (unit) {
        units->insert(unit);
        field->addUnit(unit);
        return true;
    }

    return false;
}


bool Facade::createFlyingUnit()
{
    auto posEnemy = enemyBase->getPosition();
    auto posBase = base->getPosition();
    srand(time(0));

    int dx = 0;
    int dy = 0;
    auto choose = rand() % 3;

    switch (choose) {
    case 1:
        dy++;
        break;
    case 2:
        dy--;
        break;
    }

    if (posBase.x < posEnemy.x) {
        dx++;
    }
    else {
        dx--;
    }

    auto unit = base->createFlyingUnit(dx, dy);
    if (unit) {
        units->insert(unit);
        field->addUnit(unit);
        return true;
    }

    return false;
}


bool Facade::attack(std::shared_ptr<unit::Unit> unit)
{
    auto posUnit = unit->getPosition();
    auto weapon = unit->getWeapon();
    auto dist = weapon->getDistanceAttack();
    auto player = unit->getPlayer();

    for (int i = posUnit.y - dist; i <= static_cast<int>(posUnit.y + dist); ++i) {
        for (int j = posUnit.x - dist; j <= static_cast<int>(posUnit.x + dist); ++j) {
            if (j < static_cast<int>(field->getWidth()) && j >= 0 &&
                    i < static_cast<int>(field->getHeight()) && i >= 0) {
                if (sqrt(pow(i - posUnit.y, 2) + pow(j - posUnit.x, 2)) <= dist) {
                    auto cell = field->getCell(Point2D(j, i));
                    if (!cell->isEmpty()) {
                        auto enemy = cell->getUnit();
                        if (enemy->getPlayer() != player) {
                            logger->writeToLog(UnitLogMsg::attackMessage(unit, enemy));
                            logger->writeToLog(UnitLogMsg::hurtMessage(enemy,
                                                                       weapon->getDamage() *
                                                                       enemy->getArmor()->getResistance()));

                                    enemy->toHurt(weapon->getDamage() *
                                                  enemy->getArmor()->getResistance());
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}


void Facade::moveUnit(std::shared_ptr<unit::Unit> unit)
{
    auto posEnemy = enemyBase->getPosition();
    auto posUnit = unit->getPosition();

    if (posUnit.x < posEnemy.x) {
        unit->moveRight();
    }
    else {
        unit->moveLeft();
    }

    if (!unit->isFly()) {
        if (posUnit.y < posEnemy.y) {
            unit->moveBottom();
        }
        else if (posUnit.y > posEnemy.y) {
            unit->moveTop();
        }
    }
    else {
        auto tmpPos = (posUnit.x + field->getWidth() / 2) / 2;
        if (posUnit.x < posEnemy.x) {
            if (static_cast<size_t>(tmpPos) <= field->getWidth() / 2) {
                if (static_cast<size_t>(posUnit.y) < field->getHeight() / 2 &&
                        static_cast<size_t>(posUnit.y) > field->getHeight() / 4) {
                    unit->moveTop();
                }
                else if (static_cast<size_t>(posUnit.y) >= field->getHeight() / 2 &&
                         static_cast<size_t>(posUnit.y) < 3 * field->getHeight() / 4) {
                    unit->moveBottom();
                }
            }
            else {
                if (posUnit.y < posEnemy.y) {
                    unit->moveBottom();
                }
                else {
                    unit->moveTop();
                }
            }
        }
        else {
            if (static_cast<size_t>(tmpPos) >= field->getWidth() / 2) {
                if (static_cast<size_t>(posUnit.y) < field->getHeight() / 2 &&
                        static_cast<size_t>(posUnit.y) > field->getHeight() / 4) {
                    unit->moveTop();
                }
                else if (static_cast<size_t>(posUnit.y) >= field->getHeight() / 2 &&
                         static_cast<size_t>(posUnit.y) < 3 * field->getHeight() / 4) {
                    unit->moveBottom();
                }
            }
            else {
                if (posUnit.y < posEnemy.y) {
                    unit->moveBottom();
                }
                else {
                    unit->moveTop();
                }
            }
        }
    }
}

