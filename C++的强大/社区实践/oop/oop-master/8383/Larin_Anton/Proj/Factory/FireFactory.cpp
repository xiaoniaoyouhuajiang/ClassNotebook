//
// Created by anton on 3/18/20.
//

#include "FireFactory.h"

FireFactory::FireFactory(Field *fld) : UnitFactory(fld) {}

GameObject *FireFactory::createUnit(UnitClass _class, UnitDevotion devotion, int x, int y) {
    return new EntityFire();
}
