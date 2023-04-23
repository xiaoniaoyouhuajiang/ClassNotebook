#include "Field.hpp"

Field::Field(int width, int height)
    : m_units(width, height)
{}

Field::Field(const Field &other)
    : m_units(other.m_units)
{
    copyUnits();
}

Field::Field(Field &&other) noexcept
    : m_units(std::move(other.m_units))
{}

Field &Field::operator=(const Field &other) {
    if (this != &other) {
        m_units = other.m_units;
        copyUnits();
    }
    return *this;
}

Field &Field::operator=(Field &&other) noexcept {
    if (this != &other) {
        m_units = std::move(other.m_units);
    }
    return *this;
}

FieldIterator Field::begin() const {
    return FieldIterator(this);
}

FieldIterator Field::end() const {
    return FieldIterator(this, true);
}

void Field::addUnit(const std::shared_ptr<Unit> &unit, FieldPosition position) {
    m_units.at(position.row, position.col) = unit;
}

void Field::removeUnit(FieldPosition position) {
    m_units.at(position.row, position.col).reset();
}

std::shared_ptr<Unit> Field::getUnit(FieldPosition position) const {
    return m_units.at(position.row, position.col);
}

int Field::getWidth() const {
    return m_units.getWidth();
}

int Field::getHeight() const {
    return m_units.getHeight();
}

void Field::copyUnits() {
    for (auto [unit, row, col] : *this) {
        m_units.at(row, col) = unit->createCopy();
    }
}
