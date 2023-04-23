#pragma once

#include <iostream>

#include "Logger.hpp"

class PlainLoggerToOstreamAdapter : public Logger {
public:
    explicit PlainLoggerToOstreamAdapter(std::ostream *os) : m_os(os) {
        if (os == nullptr)
            throw std::runtime_error("Error: 'os' is nullptr.");
    }

    void logGameStarting() override {
        *m_os << "New game is started." << std::endl;
    }
    void logUnitCreation(std::shared_ptr<const Unit> unit, FieldPosition position) override {
        *m_os << unit->getName() << " is created at " << position << std::endl;
    }
    void logUnitMovement(std::shared_ptr<const Unit> unit, FieldPosition oldPosition, FieldPosition newPosition) override {
        *m_os << unit->getName() << " is moved from " << oldPosition << " to " << newPosition << std::endl;
    }
    void logAttack(std::shared_ptr<const Unit> attacker, FieldPosition attackerPosition, std::shared_ptr<const Creature> victim, FieldPosition victimPosition, int oldHealth) override {
        *m_os << attacker->getName() << " at " << attackerPosition << " has attacked " << victim->getName() << " at " << victimPosition
            << ", old health = " << oldHealth << ", new health = " << victim->getHealth() << std::endl;
    }
    void logThingApplying(std::shared_ptr<const Unit> unit, std::shared_ptr<const Thing> thing, int oldHealth) override {
        *m_os << thing->getName() << " has been applied to " << unit->getName()
            << ", old health = " << oldHealth << ", new health = " << unit->getHealth() << std::endl;
    }

protected:
    std::ostream *m_os;
};