//
// Created by anton on 3/17/20.
//

#include "BushFactory.h"

BushFactory::BushFactory(Field *fld) : UnitFactory(fld) {}

GameObject *BushFactory::createUnit(UnitClass _class, UnitDevotion devotion, int x, int y) {
    return new EntityBush();
}
