#include "Field.hpp"

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
    if (unitFactory == nullptr)
        return;
    auto cell = m_cells.at(position.row, position.col);
    if (cell->getCreature() != nullptr)
        return;
    cell->setUnit(unitFactory->create());
}

void Field::moveUnit(FieldPosition unitPosition, FieldPosition targetPosition) {
    auto unitCell = m_cells.at(unitPosition.row, unitPosition.col);
    auto targetCell = m_cells.at(targetPosition.row, targetPosition.col);
    if (unitCell->getUnit() == nullptr || targetCell->getCreature() != nullptr)
        return;
    targetCell->setUnit(unitCell->getUnit());
    unitCell->removeCreature();
}

void Field::removeCreature(FieldPosition position) {
    auto cell = m_cells.at(position.row, position.col);
    if (cell->getUnit() != nullptr)
        cell->getUnit()->notifyAboutDeletionFromField();
    cell->removeCreature();
}

void Field::setTerrain(const std::shared_ptr<const TerrainFactory> &terrainFactory, FieldPosition position) {
    if (terrainFactory != nullptr)
        m_cells.at(position.row, position.col)->setTerrain(terrainFactory->create());
}

std::shared_ptr<Base> Field::createBase(FieldPosition basePosition, int player) {
    auto cell = m_cells.at(basePosition.row, basePosition.col);
    if (cell->getCreature() != nullptr)
        return nullptr;
    auto base = std::make_shared<Base>(player, *this, basePosition);
    cell->setBase(base);
    return base;
}
