#include "mediator.h"

#include "Unit/unit.h"

#include "Field/gamefield.h"

#include "Logger/logger.h"
#include "Logger/unitlogmsg.h"


using namespace unit;


Mediator::Mediator(std::shared_ptr<GameField> gameField,
                   std::shared_ptr<Logger> logger)
{
    this->gameField = gameField;
    this->logger = logger;
}


bool Mediator::notify(std::shared_ptr<Unit> unit,
                      const std::string& act)
{
    Point2D currentPoint = unit->getPosition();
    auto currentCell = gameField->getCell(currentPoint);
    Point2D nextPoint = currentPoint;

    if (act == MOVE_TOP || act == MOVE_LEFT ||
            act == MOVE_RIGHT || act == MOVE_BOTTOM) {
        if (act == MOVE_TOP) {
            nextPoint.y--;
            if (nextPoint.y < 0) {
                logger->writeToLog(UnitLogMsg::moveMessage(unit, currentPoint,
                                                           nextPoint), LVL::ERR);
                return false;
            }
        }
        else if (act == MOVE_LEFT) {
            nextPoint.x--;
            if (nextPoint.x < 0) {
                logger->writeToLog(UnitLogMsg::moveMessage(unit, currentPoint,
                                                           nextPoint), LVL::ERR);
                return false;
            }
        }
        else if (act == MOVE_RIGHT) {
            nextPoint.x++;
            if (nextPoint.x >= static_cast<int>(gameField->getWidth())) {
                logger->writeToLog(UnitLogMsg::moveMessage(unit, currentPoint,
                                                           nextPoint), LVL::ERR);
                return false;
            }

        }
        else if (act == MOVE_BOTTOM) {
            nextPoint.y++;
            if (nextPoint.y >= static_cast<int>(gameField->getHeight())) {
                logger->writeToLog(UnitLogMsg::moveMessage(unit, currentPoint,
                                                           nextPoint), LVL::ERR);
                return false;
            }
        }

        auto nextCell = gameField->getCell(nextPoint);

        if (nextCell->isEmpty() && nextCell->getLandscape()->canMove(unit)) {
            logger->writeToLog(UnitLogMsg::moveMessage(unit, currentPoint,
                                                       nextPoint));
            nextCell->addUnit(unit);
            nextCell->getLandscape()->hurtUnit(unit);
            currentCell->deleteUnit();
            (*nextCell->getNeutralObject())[unit];
            nextCell->deleteNeutralObject();
            return true;
        }

        logger->writeToLog(UnitLogMsg::moveMessage(unit, currentPoint,
                                                   nextPoint), LVL::ERR);
    }
    else if (act == CRT_UNIT) {
        if (currentCell->isEmpty()) {
            logger->writeToLog(UnitLogMsg::createMessage(unit));
            currentCell->addUnit(unit);
            return true;
        }

        logger->writeToLog(UnitLogMsg::createMessage(unit), LVL::ERR);
    }

    return false;
}
