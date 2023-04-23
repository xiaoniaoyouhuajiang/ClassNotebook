//
// Created by anton on 2/22/20.
//

#include "BetaFactory.h"

GameObject *BetaFactory::createUnit(UnitClass _class, UnitDevotion devotion, int x, int y) {
    Beta *u = new Beta(fld, x, y, 0, devotion);
    //Beta* u = new Beta(fld,x,y,0,devotion,0,this,)
    return u;
}

BetaFactory::BetaFactory(Field *fld) : UnitFactory(fld) {}

//BetaFactory::BetaFactory(Field *fld, CommonFactory *commonFactory) : UnitFactory(fld, commonFactory) {}
