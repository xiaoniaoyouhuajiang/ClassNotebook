//
// Created by anton on 3/18/20.
//

#ifndef PROJ_STONEFACTORY_H
#define PROJ_STONEFACTORY_H


#include "UnitFactory.h"

class StoneFactory : UnitFactory {
    friend class CommonFactory;

public:
    StoneFactory(Field *fld);

private:
    GameObject *createUnit(UnitClass _class, UnitDevotion devotion, int x, int y) override;

};


#endif //PROJ_STONEFACTORY_H
