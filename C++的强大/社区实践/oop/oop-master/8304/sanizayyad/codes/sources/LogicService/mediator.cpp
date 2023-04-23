#include "mediator.hpp"
#include "BattleField.hpp"
#include "unit.hpp"
#include "poisonobject.hpp"
#include "proxy.hpp"
using namespace unit;

Mediator::Mediator(std::shared_ptr<BattleField> battleField, std::shared_ptr<Proxy> proxyLog)
{
    this->battleField = battleField;
    this->proxyLog = proxyLog;
}


bool Mediator::notify(std::shared_ptr<unit::Unit> unit,const std::string& action)
{
    Position2D currentPosition = unit->getPosition();
    auto currentCell = battleField->getFieldCell(currentPosition);
    Position2D nextPoint = currentPosition;

    if(action == MOVE_TOP || action == MOVE_LEFT ||
    action == MOVE_RIGHT || action == MOVE_BOTTOM){
        if (action == MOVE_TOP) {
            nextPoint.y--;
            if (nextPoint.y < 0) {
                proxyLog->logMessage(UnitLog::moveMessage(unit, currentPosition,nextPoint), TYPE::ERR);
                return false;
            }
        }
        else if (action == MOVE_LEFT) {
            nextPoint.x--;
            if (nextPoint.x < 0) {
                proxyLog->logMessage(UnitLog::moveMessage(unit, currentPosition,nextPoint), TYPE::ERR);
                return false;
            }
        }
        else if (action == MOVE_RIGHT) {
            nextPoint.x++;
            if (nextPoint.x >= static_cast<int>(battleField->getWidth())) {
                proxyLog->logMessage(UnitLog::moveMessage(unit, currentPosition,nextPoint), TYPE::ERR);
                return false;
            }
        }
        else if (action == MOVE_BOTTOM) {
            nextPoint.y++;
            if (nextPoint.y >= static_cast<int>(battleField->getHeight())) {
                proxyLog->logMessage(UnitLog::moveMessage(unit, currentPosition,nextPoint), TYPE::ERR);
                return false;
            }
        }
        
        auto nextCell = battleField->getFieldCell(nextPoint);
                
        if (nextCell->isEmpty() && nextCell->getLandscape()->canMove(unit)) {
            proxyLog->logMessage(UnitLog::moveMessage(unit, currentPosition,nextPoint));
            nextCell->addUnit(unit);
            nextCell->getLandscape()->hurtUnit(unit);
            currentCell->deleteUnit();
            (*nextCell->getNeutralObject())[unit];
            nextCell->deleteNeutralObject();
            return true;
        }
        proxyLog->logMessage(UnitLog::moveMessage(unit, currentPosition,nextPoint), TYPE::ERR);

        
    }else if (action == CREATE_UNIT){
        if (currentCell->isEmpty()) {
            proxyLog->logMessage(UnitLog::createMessage(unit));
            currentCell->addUnit(unit);
            return true;
        }
        proxyLog->logMessage(UnitLog::createMessage(unit), TYPE::ERR);
    }
    return false;
}
