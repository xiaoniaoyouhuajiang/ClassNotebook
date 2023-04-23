//
// Created by anton on 3/18/20.
//

#include "TreeFactory.h"

TreeFactory::TreeFactory(Field *fld) : UnitFactory(fld) {}

GameObject *TreeFactory::createUnit(UnitClass _class, UnitDevotion devotion, int x, int y) {
    return new EntityTree();
}
    