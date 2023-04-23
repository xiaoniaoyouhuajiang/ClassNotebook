//
// Created by anton on 2/22/20.
//

#ifndef PROJ_BETAFACTORY_H
#define PROJ_BETAFACTORY_H


#include "UnitFactory.h"

class BetaFactory : UnitFactory {
    friend class CommonFactory;

public:
    BetaFactory(Field *fld);

    //BetaFactory(Field *fld, CommonFactory *commonFactory);

private:
    GameObject *createUnit(UnitClass _class, UnitDevotion devotion, int x, int y) override;
};


#endif //PROJ_BETAFACTORY_H
