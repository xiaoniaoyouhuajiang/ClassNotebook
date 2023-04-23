#pragma once

#include <memory>
#include <set>

#include "Field/Field.hpp"
#include "Units/Unit.hpp"
#include "Units/UnitFactory.hpp"

class Game {
public:
    Game();
    Game &operator=(const Game&) = delete;

    void start(int width, int height);

    std::shared_ptr<const Field> getField() const;

    void createUnit(const std::shared_ptr<const UnitFactory> &unitFactory, FieldPosition basePosition);

    std::set<FieldPosition> findPossibleMoves(FieldPosition unitPosition) const;
    void move(FieldPosition unitPosition, FieldPosition targetPosition);

    std::set<FieldPosition> findPossibleAttacks(FieldPosition unitPosition) const;
    void attack(FieldPosition attackerPosition, FieldPosition victimPosition);

private:
    std::shared_ptr<Field> m_field;
};
