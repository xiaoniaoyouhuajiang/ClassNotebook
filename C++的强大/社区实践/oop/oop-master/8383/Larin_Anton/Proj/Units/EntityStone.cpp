//
// Created by anton on 3/4/20.
//

#include "EntityStone.h"

wchar_t EntityStone::toChar() {
    return '#';
}

bool EntityStone::die(const GameObject &src, GameObject &dst) {
    return GameObject::die(src, dst);
}

GameObject &EntityStone::operator+=(const LandscapeProxy &b) {
    return *this;
}

GameObject &EntityStone::operator+=(const FieldCellProxy &b) {
    this->operator+=(b.getLandscape());
    return *this;
}

GameObject &EntityStone::operator-=(const GameObject &b) {
    return *this;
}

EntityStone::EntityStone() {}

bool EntityStone::isValidStep(int x, int y) {
    return false;
}

bool EntityStone::step(int x, int y) {
    return false;
}

UnitClass EntityStone::getUnitClass() const {
    return UnitClass::STONE;
}
