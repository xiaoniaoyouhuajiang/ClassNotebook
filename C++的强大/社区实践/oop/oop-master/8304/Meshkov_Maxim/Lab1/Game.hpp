#pragma once

#include <memory>
#include <set>


#include "Field.hpp"
#include "FieldPosition.hpp"
#include "Units/Unit.hpp"

class Game {
public:
    Game();
    Game &operator=(const Game&) = delete;

    void start(int width, int height);

    int getFieldWidth() const;
    int getFieldHeight() const;
    FieldIterator getFieldBegin() const;
    FieldIterator getFieldEnd() const;

    bool cellHasUnit(FieldPosition position) const;
    const Unit &getUnit(FieldPosition unitPosition) const;
    void addUnitOfSameType(const Unit &unitToTakeType, FieldPosition unitPosition);

    std::set<FieldPosition> findPossibleMoves(FieldPosition unitPosition) const;
    void move(FieldPosition unitPosition, FieldPosition targetPosition);

    // TODO
//    std::set<FieldPosition> findPossibleAttacks(FieldPosition unitPosition, FieldPosition attackPosition) const;
//    void attack(FieldPosition unitPosition, FieldPosition attackPosition);

private:
    std::unique_ptr<Field> m_field;
};
