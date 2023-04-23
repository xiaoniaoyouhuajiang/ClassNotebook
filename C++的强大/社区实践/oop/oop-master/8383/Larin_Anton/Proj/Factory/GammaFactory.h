//
// Created by anton on 2/22/20.
//

#ifndef PROJ_GAMMAFACTORY_H
#define PROJ_GAMMAFACTORY_H


#include "UnitFactory.h"

class GammaFactory : UnitFactory {
    friend class CommonFactory;

public:
    GammaFactory(Field *fld);

private:
    GameObject *createUnit(UnitClass _class, UnitDevotion devotion, int x, int y) override;

};


#endif //PROJ_GAMMAFACTORY_H
