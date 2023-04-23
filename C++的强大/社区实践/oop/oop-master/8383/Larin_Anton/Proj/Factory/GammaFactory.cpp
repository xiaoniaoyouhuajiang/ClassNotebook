//
// Created by anton on 2/22/20.
//

#include "GammaFactory.h"

GameObject *GammaFactory::createUnit(UnitClass _class, UnitDevotion devotion, int x, int y) {
    Gamma *u = new Gamma(fld, x, y, 0, devotion);
    return u;
}

GammaFactory::GammaFactory(Field *fld) : UnitFactory(fld) {}
