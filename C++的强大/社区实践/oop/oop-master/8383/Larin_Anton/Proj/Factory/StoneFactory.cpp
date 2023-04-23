//
// Created by anton on 3/18/20.
//

#include "StoneFactory.h"

StoneFactory::StoneFactory(Field *fld) : UnitFactory(fld) {}

GameObject *StoneFactory::createUnit(UnitClass _class, UnitDevotion devotion, int x, int y) {
    return new EntityStone();
}
