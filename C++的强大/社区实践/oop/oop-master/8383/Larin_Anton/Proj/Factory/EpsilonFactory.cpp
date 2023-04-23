//
// Created by anton on 2/22/20.
//

#include "EpsilonFactory.h"

GameObject *EpsilonFactory::createUnit(UnitClass _class, UnitDevotion devotion, int x, int y) {
    Epsilon *u = new Epsilon(fld, x, y, 0, devotion);
    return u;
}

EpsilonFactory::EpsilonFactory(Field *fld) : UnitFactory(fld) {}
