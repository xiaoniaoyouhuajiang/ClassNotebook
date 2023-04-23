#include "FieldCell.hpp"

#include "../Terrains/GroundTerrain.hpp"

FieldCell::FieldCell()
    : m_terrain(new GroundTerrain)
{}

FieldCell::FieldCell(const FieldCell &other) {
    *this = other;
}

FieldCell &FieldCell::operator=(const FieldCell &other) {
    if (&other != this) {
        m_unit = other.m_unit->createCopy();
        m_terrain = other.m_terrain->createCopy();
        m_base = other.m_base; // TODO
    }
    return *this;
}

void FieldCell::removeCreature() {
    m_unit.reset();
    m_base.reset();
}

bool FieldCell::canHoldSomething() const {
    return m_terrain->canHoldSomething() && m_unit == nullptr && m_base == nullptr;
}
