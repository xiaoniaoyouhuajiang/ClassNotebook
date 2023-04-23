//
// Created by anton on 3/17/20.
//

#ifndef PROJ_BUSHFACTORY_H
#define PROJ_BUSHFACTORY_H


#include "UnitFactory.h"

class BushFactory : UnitFactory {
    friend class CommonFactory;

public:
    BushFactory(Field *fld);

private:
    GameObject *createUnit(UnitClass _class, UnitDevotion devotion, int x, int y) override;

};


#endif //PROJ_BUSHFACTORY_H
