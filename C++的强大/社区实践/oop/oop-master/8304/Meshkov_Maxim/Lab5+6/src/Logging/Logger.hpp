#pragma once

#include "../Units/Unit.hpp"
#include "../Things/Thing.hpp"

class Logger {
public:
    virtual void logGameStarting() = 0;
    virtual void logUnitCreation(std::shared_ptr<const Unit> unit, FieldPosition position) = 0;
    virtual void logUnitMovement(std::shared_ptr<const Unit> unit, FieldPosition oldPosition, FieldPosition newPosition) = 0;
    virtual void logAttack(std::shared_ptr<const Unit> attacker, FieldPosition attackerPosition, std::shared_ptr<const Creature> victim, FieldPosition victimPosition, int oldHealth) = 0;
    virtual void logThingApplying(std::shared_ptr<const Unit> unit, std::shared_ptr<const Thing> thing, int oldHealth) = 0;
};