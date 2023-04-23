//
// Created by anton on 2/12/20.
//

#include "Epsilon.h"

#include "../LandscapeProxy.h"

wchar_t Epsilon::toChar() {
    //return L'ε';
    return L'e';
}

UnitClass Epsilon::getUnitClass() const {
    return UnitClass::EPSILON;
}

int Epsilon::getPower() {
    int _x, _y;
    this->getCoords(_x, _y);
    return mediator->getOrdAt(_x,_y,getUnitDevotion());;//TODO
}

bool Epsilon::isValidStep(int x, int y) {
    return true;
}

bool Epsilon::step(int x, int y) {
    if (isValidStep(x, y)) {
        GameObject::setCoords(x, y);
        return true;
    }
    return false;
}

Epsilon::Epsilon(Field *fld, int x, int y, int health, UnitDevotion devotion, bool active) : Mage(fld, x, y, health,
                                                                                                  devotion, active) {}

GameObject &Epsilon::operator+=(const LandscapeProxy &b) {
    ord = b.getOrd(this->getUnitDevotion());
    return *this;
}

GameObject &Epsilon::operator+=(const FieldCellProxy &b) {
    this->operator+=(b.getLandscape());
    return *this;//TODO
}

GameObject &Epsilon::operator-=(const GameObject &b) {
    return *this;//TODO
}
