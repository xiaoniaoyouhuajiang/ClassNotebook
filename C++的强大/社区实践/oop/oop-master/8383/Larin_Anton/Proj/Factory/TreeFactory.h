//
// Created by anton on 3/18/20.
//

#ifndef PROJ_TREEFACTORY_H
#define PROJ_TREEFACTORY_H


#include "UnitFactory.h"

class TreeFactory : UnitFactory {
    friend class CommonFactory;

public:
    TreeFactory(Field *fld);

private:
    GameObject *createUnit(UnitClass _class, UnitDevotion devotion, int x, int y) override;

};


#endif //PROJ_TREEFACTORY_H
