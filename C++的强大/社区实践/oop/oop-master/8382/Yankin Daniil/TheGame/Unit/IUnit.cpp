#include <typeinfo>
#include "IUnit.h"
#include "Landscape/LandscapeHeader.h"
#include "Player/Player.h"
#include "Base/Base.h"
#include "UnitGroup.h"
#include "Game/Game.h"


IUnit::IUnit() {}


uint16_t IUnit::getGroupType() {
    return UNIT;
}


bool IUnit::move(Point point) {
    bool result = false;

    Game& game = Game::getInstance();
    if (game.getGameMediator().unitMove(this, point)) {
        setMovePoints(getMovePoints() - Game::getInstance().getGameMediator().getLandscape(point)->getMovementCost());
        setPoint(point);

        bool alive = game.getGameMediator().unitNeutralInterraction(this);

        if (alive) {
            game.unitWasMoved(this);
            result = true;
        }
        else {
            result = false;
        }

        if (game.exist()) {
            Game::getInstance().checkEndGame();
        }
    }
    return result;
}

void IUnit::attack(IUnit* defender) {
    if (checkAttacked()) {
        return;
    }

    Game& game = Game::getInstance();
    GameMediator& mediator = Game::getInstance().getGameMediator();

    if (getAttackRadius() == 0) {
        if (!mediator.checkNeighborPoint(getPoint(), defender->getPoint()))
            return;

        if (getMovePoints() < mediator.getLandscape(defender->getPoint())->getMovementCost())
            return;

        Point defenderPoint = defender->getPoint();

        uint16_t attackerDamage = giveDamage(defender);
        uint16_t defenderDamage = defender->giveDamage(this);

        std::vector<int> attLogParameters = {getObjectType(), getPoint().getX(), getPoint().getY(), getPlayer()->getColor(),
                                               defender->getObjectType(), defender->getPoint().getX(), defender->getPoint().getY(), defender->getPlayer()->getColor(),
                                               attackerDamage};
        std::vector<int> defLogParameters = {defender->getObjectType(), defender->getPoint().getX(), defender->getPoint().getY(), defender->getPlayer()->getColor(),
                                               getObjectType(), getPoint().getX(), getPoint().getY(), getPlayer()->getColor(),
                                               defenderDamage};

        game.getLogAdapter().log(LOG_ATTACK, attLogParameters);
        bool defenderALive = defender->takeDamage(attackerDamage);

        game.getLogAdapter().log(LOG_DEFEND, defLogParameters);
        bool attackerALive = takeDamage(defenderDamage);

        if (!defenderALive && attackerALive) {
            move(defenderPoint);
        }

        if (attackerALive && game.exist()) {
            game.getGameFacade().setVisualUnitPos(this);
        }
    }
    else {
        if (getAttackRadius() < mediator.distance(getPoint(), defender->getPoint()))
            return;

        uint16_t attackerDamage = giveDamage(defender);

        std::vector<int> logParameters = {getObjectType(), getPoint().getX(), getPoint().getY(), getPlayer()->getColor(),
                                               defender->getObjectType(), defender->getPoint().getX(), defender->getPoint().getY(), defender->getPlayer()->getColor(),
                                               attackerDamage};
        game.getLogAdapter().log(LOG_ATTACK, logParameters);

        defender->takeDamage(attackerDamage);
    }

    if (game.exist()) {
        setAttacked();
        game.checkEndGame();
    }
}

void IUnit::attack(Base* defender) {
    if (checkAttacked()) {
        return;
    }

    Game& game = Game::getInstance();
    GameMediator& mediator = Game::getInstance().getGameMediator();

    if (getAttackRadius() == 0) {
        if (!mediator.checkNeighborPoint(getPoint(), defender->getPoint()))
            return;

        if (getMovePoints() < mediator.getLandscape(defender->getPoint())->getMovementCost())
            return;

        Point defenderPoint = defender->getPoint();

        uint16_t attackerDamage = giveDamage(defender);
        uint16_t defenderDamage = defender->giveDamage(this);

        std::vector<int> attLogParameters = {getObjectType(), getPoint().getX(), getPoint().getY(), getPlayer()->getColor(),
                                               defender->getObjectType(), defender->getPoint().getX(), defender->getPoint().getY(), defender->getPlayer()->getColor(),
                                               attackerDamage};
        std::vector<int> defLogParameters = {defender->getObjectType(), defender->getPoint().getX(), defender->getPoint().getY(), defender->getPlayer()->getColor(),
                                               getObjectType(), getPoint().getX(), getPoint().getY(), getPlayer()->getColor(),
                                               defenderDamage};

        game.getLogAdapter().log(LOG_ATTACK, attLogParameters);
        bool defenderALive = defender->takeDamage(attackerDamage);

        game.getLogAdapter().log(LOG_DEFEND, defLogParameters);
        bool attackerALive = takeDamage(defenderDamage);

        if (!defenderALive && attackerALive) {
            move(defenderPoint);
        }

        if (attackerALive && game.exist()) {
            game.getGameFacade().setVisualUnitPos(this);
        }
    }
    else {
        if (getAttackRadius() < mediator.distance(getPoint(), defender->getPoint()))
            return;

        uint16_t attackerDamage = giveDamage(defender);

        std::vector<int> logParameters = {getObjectType(), getPoint().getX(), getPoint().getY(), getPlayer()->getColor(),
                                          defender->getObjectType(), defender->getPoint().getX(), defender->getPoint().getY(), defender->getPlayer()->getColor(),
                                          attackerDamage};
        game.getLogAdapter().log(LOG_ATTACK, logParameters);

        defender->takeDamage(attackerDamage);
    }

    if (game.exist()) {
        setAttacked();
        game.checkEndGame();
    }
}

void IUnit::unite(IUnit* passive) {
    if (!Game::getInstance().getGameMediator().unitUnificationAccess(this, passive))
        return;

    std::vector<int> logParameters = {getObjectType(), getPoint().getX(), getPoint().getY(), passive->getPoint().getX(), passive->getPoint().getY(),
                                          getPlayer()->getColor()};

    if (typeid (*this) != typeid (UnitGroup) && typeid (*passive) != typeid (UnitGroup)) {
        setMovePoints(getMovePoints() - Game::getInstance().getGameMediator().getLandscape(getPoint())->getMovementCost());

        std::vector <Unit*> details;
        details.push_back(static_cast <Unit*> (this));
        details.push_back(static_cast <Unit*> (passive));

        new UnitGroup(details);

        Game::getInstance().getLogAdapter().log(LOG_UNITE, logParameters);
    }

    else if (typeid (*this) == typeid (UnitGroup) && typeid (*passive) != typeid (UnitGroup)) {
        UnitGroup* activeGroup = static_cast <UnitGroup*> (this);
        Unit* passiveUnit = static_cast <Unit*> (passive);

        if (activeGroup->getGroupSize() + 1 >= activeGroup->getMaxGroupSize())
            return;

        activeGroup->join(passiveUnit, true);
    }

    else if (typeid (*this) != typeid (UnitGroup) && typeid (*passive) == typeid (UnitGroup)) {
        Unit* activeUnit = static_cast <Unit*> (this);
        UnitGroup* passiveGroup = static_cast <UnitGroup*> (passive);

        if (passiveGroup->getGroupSize() + 1 >= passiveGroup->getMaxGroupSize())
            return;

        passiveGroup->join(activeUnit, false);
    }

    else if (typeid (*this) == typeid (UnitGroup) && typeid (*passive) == typeid (UnitGroup)) {
        UnitGroup* activeGroup = static_cast <UnitGroup*> (this);
        UnitGroup* passiveGroup = static_cast <UnitGroup*> (passive);

        if (activeGroup->getGroupSize() + passiveGroup->getGroupSize() > activeGroup->getMaxGroupSize())
            return;

        activeGroup->join(passiveGroup, true);
    }

    Game::getInstance().getLogAdapter().log(LOG_UNITE, logParameters);
}
