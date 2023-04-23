#pragma once

#include <memory>
#include <set>

#include "Field/Field.hpp"
#include "Units/Unit.hpp"
#include "Units/UnitFactory.hpp"

class GameInterface {
public:
    virtual void start(int width, int height) = 0;

    virtual std::shared_ptr<const Field> getField() const = 0;

    virtual FieldPosition createUnit(const std::shared_ptr<const UnitFactory> &unitFactory, FieldPosition basePosition) = 0;

    virtual std::set<FieldPosition> findPossibleMoves(FieldPosition unitPosition) const = 0;
    virtual void move(FieldPosition unitPosition, FieldPosition targetPosition) = 0;

    virtual std::set<FieldPosition> findPossibleAttacks(FieldPosition unitPosition) const = 0;
    virtual void attack(FieldPosition attackerPosition, FieldPosition victimPosition) = 0;
};