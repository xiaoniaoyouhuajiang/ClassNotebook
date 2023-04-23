#pragma once

#include "PlainLoggerToOstreamAdapter.hpp"

#include <iomanip>

class WithTimeLoggerToOstreamAdapter : public PlainLoggerToOstreamAdapter {
public:
    explicit WithTimeLoggerToOstreamAdapter(std::ostream *os) : PlainLoggerToOstreamAdapter(os) {
    }

    void printTime() {
        auto t = time(nullptr);
        *m_os << std::put_time(localtime(&t), "%F %T") << ": ";
    }
    void logGameStarting() override {
        printTime();
        PlainLoggerToOstreamAdapter::logGameStarting();
    }
    void logUnitCreation(std::shared_ptr<const Unit> unit, FieldPosition position) override {
        printTime();
        PlainLoggerToOstreamAdapter::logUnitCreation(unit, position);
    }
    void logUnitMovement(std::shared_ptr<const Unit> unit, FieldPosition oldPosition, FieldPosition newPosition) override {
        printTime();
        PlainLoggerToOstreamAdapter::logUnitMovement(unit, oldPosition, newPosition);
    }
    void logAttack(std::shared_ptr<const Unit> attacker, FieldPosition attackerPosition, std::shared_ptr<const Creature> victim, FieldPosition victimPosition, int oldHealth) override {
        printTime();
        PlainLoggerToOstreamAdapter::logAttack(attacker, attackerPosition, victim, victimPosition, oldHealth);
    }
    void logThingApplying(std::shared_ptr<const Unit> unit, std::shared_ptr<const Thing> thing, int oldHealth) override {
        printTime();
        PlainLoggerToOstreamAdapter::logThingApplying(unit, thing, oldHealth);
    }
};