//
// Created by anton on 2/22/20.
//

#include "DeltaFactory.h"

GameObject *DeltaFactory::createUnit(UnitClass _class, UnitDevotion devotion, int x, int y) {
    Delta *u = new Delta(fld, x, y, 0, devotion);
    return u;
}

DeltaFactory::DeltaFactory(Field *fld) : UnitFactory(fld) {}
