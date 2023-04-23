//
// Created by anton on 3/4/20.
//

#include "EntityFire.h"

wchar_t EntityFire::toChar() {
    return '*';
}

bool EntityFire::die(const GameObject &src, GameObject &dst) {
    return GameObject::die(src, dst);
}

GameObject &EntityFire::operator+=(const LandscapeProxy &b) {
    return *this;
}

GameObject &EntityFire::operator+=(const FieldCellProxy &b) {
    this->operator+=(b.getLandscape());
    return *this;
}

GameObject &EntityFire::operator-=(const GameObject &b) {
    return *this;
}

EntityFire::EntityFire() {}

bool EntityFire::isValidStep(int x, int y) {
    return false;
}

bool EntityFire::step(int x, int y) {
    return false;
}

UnitClass EntityFire::getUnitClass() const {
    return UnitClass::FIRE;
}
