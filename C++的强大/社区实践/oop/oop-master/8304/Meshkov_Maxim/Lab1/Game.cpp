#include "Game.hpp"

#include <exception>
#include <cmath>

Game::Game()
    : m_field(new Field(0, 0))
{}

void Game::start(int width, int height) {
    m_field.reset(new Field(width, height));
}

int Game::getFieldWidth() const {
    return m_field->getWidth();
}

int Game::getFieldHeight() const {
    return m_field->getHeight();
}

FieldIterator Game::getFieldBegin() const {
    return m_field->begin();
}

FieldIterator Game::getFieldEnd() const {
    return m_field->end();
}

bool Game::cellHasUnit(FieldPosition position) const {
    return m_field->getUnit(position) != nullptr;
}

const Unit &Game::getUnit(FieldPosition unitPosition) const {
    if (!cellHasUnit(unitPosition))
        throw std::runtime_error("Cell has no unit.");
    return *(m_field->getUnit(unitPosition));
}

void Game::addUnitOfSameType(const Unit &unitToTakeType, FieldPosition unitPosition) {
    m_field->addUnit(unitToTakeType.createNewOfSameType(), unitPosition);
}

std::set<FieldPosition> Game::findPossibleMoves(FieldPosition unitPosition) const {
    if (!cellHasUnit(unitPosition))
        return {};
    // TODO refactoring
    int maxMoveDistance = m_field->getUnit(unitPosition)->getMoveRange();
    int rowStart = std::max(unitPosition.row - maxMoveDistance, 0);
    int colStart = std::max(unitPosition.col - maxMoveDistance, 0);
    int rowEnd = std::min(unitPosition.row + maxMoveDistance, m_field->getHeight() - 1);
    int colEnd = std::min(unitPosition.col + maxMoveDistance, m_field->getWidth() - 1);
    std::set<FieldPosition> possibleMoves;
    for (int row = rowStart; row <= rowEnd; row++) {
        for (int col = colStart; col <= colEnd; col++) {
            int rowDiffSquare = std::pow(row - unitPosition.row, 2);
            int colDiffSquare = std::pow(col - unitPosition.col, 2);
            if (rowDiffSquare + colDiffSquare <= std::pow(maxMoveDistance, 2)) {
                possibleMoves.insert({row, col});
            }
        }
    }
    return possibleMoves;
}

void Game::move(FieldPosition unitPosition, FieldPosition movePosition) {
    auto possibleMoves = findPossibleMoves(unitPosition);
    if (possibleMoves.find(movePosition) == possibleMoves.end())
        throw std::runtime_error("Impossible move.");
    auto unit = m_field->getUnit(unitPosition);
    m_field->removeUnit(unitPosition);
    m_field->addUnit(unit, movePosition);
}
