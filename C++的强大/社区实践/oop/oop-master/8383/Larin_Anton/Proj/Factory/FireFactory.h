//
// Created by anton on 3/18/20.
//

#ifndef PROJ_FIREFACTORY_H
#define PROJ_FIREFACTORY_H


#include "UnitFactory.h"

class FireFactory : UnitFactory {
    friend class CommonFactory;

public:
    FireFactory(Field *fld);

private:
    GameObject *createUnit(UnitClass _class, UnitDevotion devotion, int x, int y) override;

};


#endif //PROJ_FIREFACTORY_H
