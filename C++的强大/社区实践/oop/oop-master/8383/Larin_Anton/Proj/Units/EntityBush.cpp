//
// Created by anton on 3/4/20.
//

#include "EntityBush.h"
//#include "../GameObject.h"


wchar_t EntityBush::toChar() {
    return '%';
}

bool EntityBush::die(const GameObject &src, GameObject &dst) {
    return false;
}

GameObject &EntityBush::operator+=(const LandscapeProxy &b) {
    return *this;
}

GameObject &EntityBush::operator+=(const FieldCellProxy &b) {
    this->operator+=(b.getLandscape());
    return *this;
}

GameObject &EntityBush::operator-=(const GameObject &b) {
    return *this;
}

EntityBush::EntityBush() {}

bool EntityBush::isValidStep(int x, int y) {
    return false;
}

bool EntityBush::step(int x, int y) {
    return false;
}

UnitClass EntityBush::getUnitClass() const {
    return UnitClass::BUSH;
}
