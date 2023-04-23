#pragma once

#include "../GameInterface.hpp"
#include "Logger.hpp"

class GameProxyWithLogging : public GameInterface {
public:
    GameProxyWithLogging(std::shared_ptr<GameInterface> game, std::shared_ptr<Logger> logger)
        : m_game(std::move(game)), m_logger(std::move(logger))
    {
        if (m_game == nullptr)
            throw std::runtime_error("Error: 'game' is nullptr.");
        if (m_logger == nullptr)
            throw std::runtime_error("Error: 'logger' is nullptr.");
    }

    void start(int width, int height) override {
        m_game->start(width, height);
        m_logger->logGameStarting();
    }

    std::shared_ptr<const Field> getField() const override {
        return m_game->getField();
    }

    FieldPosition createUnit(const std::shared_ptr<const UnitFactory> &unitFactory, FieldPosition basePosition) override {
        auto unitPosition = m_game->createUnit(unitFactory, basePosition);
        m_logger->logUnitCreation(m_game->getField()->getCell(unitPosition)->getUnit(), unitPosition);
        return unitPosition;
    }

    std::set<FieldPosition> findPossibleMoves(FieldPosition unitPosition) const override {
        return m_game->findPossibleMoves(unitPosition);
    }
    void move(FieldPosition unitPosition, FieldPosition targetPosition) override {
        auto unit = m_game->getField()->getCell(unitPosition)->getUnit();
        auto thing = m_game->getField()->getCell(targetPosition)->getThing();
        auto oldHealth = unit->getHealth();
        m_game->move(unitPosition, targetPosition);
        m_logger->logUnitMovement(unit, unitPosition, targetPosition);
        if (thing != nullptr)
            m_logger->logThingApplying(unit, thing, oldHealth);
    }

    std::set<FieldPosition> findPossibleAttacks(FieldPosition unitPosition) const override {
        return m_game->findPossibleAttacks(unitPosition);
    }
    void attack(FieldPosition attackerPosition, FieldPosition victimPosition) override {
        auto victim = m_game->getField()->getCell(victimPosition)->getCreature();
        auto oldHealth = victim->getHealth();
        m_game->attack(attackerPosition, victimPosition);
        auto attacker = m_game->getField()->getCell(attackerPosition)->getUnit();
        m_logger->logAttack(attacker, attackerPosition, victim, victimPosition, oldHealth);
    }

private:
    std::shared_ptr<GameInterface> m_game;
    std::shared_ptr<Logger> m_logger;
};
