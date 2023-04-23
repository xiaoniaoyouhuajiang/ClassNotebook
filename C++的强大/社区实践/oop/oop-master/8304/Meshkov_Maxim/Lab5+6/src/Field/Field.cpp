#include "Field.hpp"

#include "../Units/Unit.hpp"
#include "../Base.hpp"

Field::Field(int width, int height)
    : m_cells(width, height)
{
    for (auto [cell, position] : *this) {
        m_cells.at(position.row, position.col) = std::make_shared<FieldCell>();
    }
}

Field::Field(const Field &other)
    : m_cells(other.m_cells)
{}

Field::Field(Field &&other) noexcept
    : m_cells(std::move(other.m_cells))
{}

Field &Field::operator=(const Field &other) {
    if (this != &other) {
        m_cells = other.m_cells;
    }
    return *this;
}

Field &Field::operator=(Field &&other) noexcept {
    if (this != &other) {
        m_cells = std::move(other.m_cells);
    }
    return *this;
}

FieldIterator Field::begin() const {
    return FieldIterator(this);
}

FieldIterator Field::end() const {
    return FieldIterator(this, true);
}

int Field::getWidth() const {
    return m_cells.getWidth();
}

int Field::getHeight() const {
    return m_cells.getHeight();
}

std::shared_ptr<const FieldCell> Field::getCell(FieldPosition position) const {
    return m_cells.at(position.row, position.col);
}

std::shared_ptr<FieldCell> Field::getCell(FieldPosition position) {
    return m_cells.at(position.row, position.col);
}

void Field::createUnit(const std::shared_ptr<const UnitFactory> &unitFactory, FieldPosition position) {
    // TODO checks if already exists
    if (unitFactory != nullptr) {
        auto cell = m_cells.at(position.row, position.col);
        cell->setUnit(unitFactory->create());
    }
}

void Field::moveUnit(FieldPosition unitPosition, FieldPosition targetPosition) {
    // TODO checks if already exist at targetPosition
    auto unitCell = m_cells.at(unitPosition.row, unitPosition.col);
    m_cells.at(targetPosition.row, targetPosition.col)->setUnit(unitCell->getUnit());
    unitCell->removeCreature();
}

void Field::removeCreature(FieldPosition position) {
    auto cell = m_cells.at(position.row, position.col);
    if (cell->getUnit() != nullptr)
        cell->getUnit()->notifyAboutDeletionFromField();
    cell->removeCreature();
}

void Field::setTerrain(const std::shared_ptr<const TerrainFactory> &terrainFactory, FieldPosition position) {
    if (terrainFactory != nullptr) {
        m_cells.at(position.row, position.col)->setTerrain(terrainFactory->create());
    }
}

std::shared_ptr<Base> Field::createBase(FieldPosition basePosition, int player) {
    auto base = std::make_shared<Base>(player, *this, basePosition);
    m_cells.at(basePosition.row, basePosition.col)->setBase(base);
    return base;
}
