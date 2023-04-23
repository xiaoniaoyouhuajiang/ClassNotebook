//
// Created by anton on 2/22/20.
//

#ifndef PROJ_EPSILONFACTORY_H
#define PROJ_EPSILONFACTORY_H


#include "UnitFactory.h"

class EpsilonFactory : UnitFactory {
    friend class CommonFactory;

public:
    EpsilonFactory(Field *fld);

private:
    GameObject *createUnit(UnitClass _class, UnitDevotion devotion, int x, int y) override;

};


#endif //PROJ_EPSILONFACTORY_H
