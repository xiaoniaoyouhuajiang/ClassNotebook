//
// Created by anton on 2/18/20.
//

#include "Zeta.h"

#include "../LandscapeProxy.h"

UnitClass Zeta::getUnitClass() const {
    return UnitClass::ZETA;
}

bool Zeta::isAllyPowered() const {
    return Fighter::isAllyPowered();
}

void Zeta::setAllyPowered(bool allyPowered) {
    Fighter::setAllyPowered(allyPowered);
}

bool Zeta::isEnemyPowered() const {
    return Fighter::isEnemyPowered();
}

void Zeta::setEnemyPowered(bool enemyPowered) {
    Fighter::setEnemyPowered(enemyPowered);
}

bool Zeta::isValidStep(int x, int y) {
    return true;
}

wchar_t Zeta::toChar() {
    //return L'ζ';
    return L'z';
}

bool Zeta::step(int x, int y) {
    if (isValidStep(x, y)) {
        GameObject::setCoords(x, y);
        return true;
    }
    return false;
}

Zeta::Zeta(Field *fld, int x, int y, int health, UnitDevotion devotion, bool active, bool allyPowered,
           bool enemyPowered) : Fighter(fld, x, y, health, devotion, active, allyPowered, enemyPowered) {}

GameObject &Zeta::operator+=(const LandscapeProxy &b) {
    return *this;
}

GameObject &Zeta::operator+=(const FieldCellProxy &b) {
    this->operator+=(b.getLandscape());
    return *this;//TODO
}

GameObject &Zeta::operator-=(const GameObject &b) {
    die(b, *this);
//    die(b,*this);
    return *this;//TODO
}
