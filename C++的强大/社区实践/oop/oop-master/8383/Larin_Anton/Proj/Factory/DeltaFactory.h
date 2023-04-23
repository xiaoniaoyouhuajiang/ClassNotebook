//
// Created by anton on 2/22/20.
//

#ifndef PROJ_DELTAFACTORY_H
#define PROJ_DELTAFACTORY_H


#include "UnitFactory.h"

class DeltaFactory : UnitFactory {
    friend class CommonFactory;

public:
    DeltaFactory(Field *fld);

private:
    GameObject *createUnit(UnitClass _class, UnitDevotion devotion, int x, int y) override;

};


#endif //PROJ_DELTAFACTORY_H
