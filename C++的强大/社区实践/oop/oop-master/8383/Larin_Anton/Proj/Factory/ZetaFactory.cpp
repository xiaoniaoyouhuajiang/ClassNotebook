//
// Created by anton on 2/22/20.
//

#include "ZetaFactory.h"

GameObject *ZetaFactory::createUnit(UnitClass _class, UnitDevotion devotion, int x, int y) {
    Zeta *u = new Zeta(fld, x, y, 0, devotion);
    return u;
}

ZetaFactory::ZetaFactory(Field *fld) : UnitFactory(fld) {}
