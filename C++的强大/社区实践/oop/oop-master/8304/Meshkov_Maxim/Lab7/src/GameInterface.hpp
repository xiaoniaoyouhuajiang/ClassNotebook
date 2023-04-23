#pragma once

#include <memory>
#include <set>

#include "Field/Field.hpp"
#include "Units/Unit.hpp"
#include "Units/UnitFactory.hpp"
#include "PlayerState.hpp"

#include "GameMemento.hpp"

class GameInterface {
public:
    virtual void start(int width, int height) = 0;

    virtual std::shared_ptr<const Field> getField() const = 0;

    virtual FieldPosition createUnit(const std::shared_ptr<const UnitFactory> &unitFactory, FieldPosition basePosition) = 0;

    virtual std::set<FieldPosition> findPossibleMoves(FieldPosition unitPosition) const = 0;
    virtual void move(FieldPosition unitPosition, FieldPosition targetPosition) = 0;

    virtual std::set<FieldPosition> findPossibleAttacks(FieldPosition unitPosition) const = 0;
    virtual void attack(FieldPosition attackerPosition, FieldPosition victimPosition) = 0;

    virtual void setPlayerState(std::shared_ptr<PlayerState> playerState) = 0;
    virtual int getCurrentPlayer() const = 0;

    virtual bool gameOver(int &winner) const = 0;

    virtual std::shared_ptr<GameMemento> createMemento() const = 0;
    virtual void restoreFromMemento(const GameMemento &memento) = 0;
};