#pragma once

#include "GameInterface.hpp"

class Game : public GameInterface {
public:
    Game();
    Game &operator=(const Game&) = delete;

    void start(int width, int height) override ;

    std::shared_ptr<const Field> getField() const override ;

    FieldPosition createUnit(const std::shared_ptr<const UnitFactory> &unitFactory, FieldPosition basePosition) override ;

    std::set<FieldPosition> findPossibleMoves(FieldPosition unitPosition) const override;
    void move(FieldPosition unitPosition, FieldPosition targetPosition) override;

    std::set<FieldPosition> findPossibleAttacks(FieldPosition unitPosition) const override;
    void attack(FieldPosition attackerPosition, FieldPosition victimPosition) override;

private:
    std::shared_ptr<Field> m_field;
};
