#include "BaseUnit.hpp"

#include <cmath>
#include <algorithm>

#include "../Field/Field.hpp"

std::optional<int> BaseUnit::getPlayer() const {
    return m_player;
}

void BaseUnit::modifyHealth(int change) {
    m_health = std::clamp(m_health + change, 0, getMaxHealth());
}

void BaseUnit::ice() {
    m_isIced = true;
}

std::set<FieldPosition> BaseUnit::findPossibleMoves(FieldPosition unitPosition, const Field &field) const {
    if (m_isIced)
        return {};
    int maxMoveDistance = getMoveRange();
    int rowStart = std::max(unitPosition.row - maxMoveDistance, 0);
    int colStart = std::max(unitPosition.col - maxMoveDistance, 0);
    int rowEnd = std::min(unitPosition.row + maxMoveDistance, field.getHeight() - 1);
    int colEnd = std::min(unitPosition.col + maxMoveDistance, field.getWidth() - 1);
    std::set<FieldPosition> possibleMoves;
    for (int row = rowStart; row <= rowEnd; row++) {
        for (int col = colStart; col <= colEnd; col++) {
            if (!field.getCell({row, col})->canHoldSomething())
                continue;
            int rowDiffSquare = std::pow(row - unitPosition.row, 2);
            int colDiffSquare = std::pow(col - unitPosition.col, 2);
            if (rowDiffSquare + colDiffSquare <= std::pow(maxMoveDistance, 2)) {
                possibleMoves.insert({row, col});
            }
        }
    }
    return possibleMoves;
}

std::set<FieldPosition> BaseUnit::findPossibleAttacks(FieldPosition unitPosition, const Field &field) const {
    // TODO? merge with findPossibleMoves
    if (m_isIced)
        return {};
    if (!field.getCell(unitPosition)->getTerrain()->unitCanAttackHere())
        return {};
    int maxAttackDistance = getMoveRange();
    int rowStart = std::max(unitPosition.row - maxAttackDistance, 0);
    int colStart = std::max(unitPosition.col - maxAttackDistance, 0);
    int rowEnd = std::min(unitPosition.row + maxAttackDistance, field.getHeight() - 1);
    int colEnd = std::min(unitPosition.col + maxAttackDistance, field.getWidth() - 1);
    std::set<FieldPosition> possibleAttacks;
    for (int row = rowStart; row <= rowEnd; row++) {
        for (int col = colStart; col <= colEnd; col++) {
            auto victim = field.getCell({row, col})->getCreature();
            if (victim == nullptr)
                continue;
            if (victim->getPlayer().has_value() && getPlayer().has_value()) {
                if (victim->getPlayer().value() == getPlayer().value())
                    continue;
            }
            int rowDiffSquare = std::pow(row - unitPosition.row, 2);
            int colDiffSquare = std::pow(col - unitPosition.col, 2);
            if (rowDiffSquare + colDiffSquare <= std::pow(maxAttackDistance, 2)) {
                possibleAttacks.insert({row, col});
            }
        }
    }
    return possibleAttacks;
}

void BaseUnit::attack(FieldPosition victimPosition, Field &field) {
    auto victim = field.getCell(victimPosition)->getCreature();
    if (victim != nullptr) {
        victim->modifyHealth(-getHit());
        if (victim->getHealth() == 0)
            field.removeCreature(victimPosition);
        auto unitVictim = field.getCell(victimPosition)->getUnit();
        if (unitVictim != nullptr && icesWhenAttacks())
            unitVictim->ice();
        return;
    }
}

std::weak_ptr<const Base> BaseUnit::getBase() const {
    return m_base;
}

void BaseUnit::setBase(std::weak_ptr<Base> base) {
    m_base = std::move(base);
    if (auto baseLocked = m_base.lock())
        m_player = baseLocked->getPlayer();
}

void BaseUnit::notifyAboutDeletionFromField() {
    if (auto base = m_base.lock())
        base->reactOnUnitDeletion(this);
}
