//
// Created by anton on 2/22/20.
//

#include "AlphaFactory.h"

GameObject *AlphaFactory::createUnit(UnitClass _class, UnitDevotion devotion, int x, int y) {
    Alpha *u = new Alpha(fld, x, y, 0, devotion, false);
    return u;
}

AlphaFactory::AlphaFactory(Field *fld) : UnitFactory(fld) {}
//AlphaFactory::AlphaFactory(Field *fld, CommonFactory *commonFactory) : UnitFactory(fld, commonFactory) {}

