//
// Created by anton on 2/12/20.
//

#include "Mage.h"


int Mage::getPower() {
    return -1;
}

Mage::Mage(Field *fld, int x, int y, int health, UnitDevotion devotion, bool active) : GameObject(fld, x, y, health,
                                                                                                  devotion, active) {}
