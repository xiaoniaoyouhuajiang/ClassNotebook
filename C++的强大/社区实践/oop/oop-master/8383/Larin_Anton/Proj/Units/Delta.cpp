//
// Created by anton on 2/12/20.
//

#include "Delta.h"

#include "../LandscapeProxy.h"

wchar_t Delta::toChar() {
    //return L'δ';
    return L'd';
}

UnitClass Delta::getUnitClass() const {
    return UnitClass::DELTA;
}

int Delta::getPower() {
    return girdle == 4 ? 1 : girdle;
}

bool Delta::isValidStep(int x, int y) {
    return true;
}

bool Delta::step(int x, int y) {
    if (isValidStep(x, y)) {
        GameObject::setCoords(x, y);
        return true;
    }
    return false;

}

Delta::Delta(Field *fld, int x, int y, int health, UnitDevotion devotion, bool active, int girdle) : Mage(fld, x, y,
                                                                                                          health,
                                                                                                          devotion,
                                                                                                          active),
                                                                                                     girdle(girdle) {/*TODO init girdle*/}

GameObject &Delta::operator+=(const LandscapeProxy &b) {
    this->girdle = b.getGirdle();
    return *this;
}

GameObject &Delta::operator+=(const FieldCellProxy &b) {
    this->operator+=(b.getLandscape());
    return *this;//TODO
}

GameObject &Delta::operator-=(const GameObject &b) {
    return *this;//TODO
}
