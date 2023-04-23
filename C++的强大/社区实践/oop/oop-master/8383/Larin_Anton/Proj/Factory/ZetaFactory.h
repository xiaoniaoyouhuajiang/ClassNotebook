//
// Created by anton on 2/22/20.
//

#ifndef PROJ_ZETAFACTORY_H
#define PROJ_ZETAFACTORY_H


#include "UnitFactory.h"

class ZetaFactory : UnitFactory {
    friend class CommonFactory;

public:
    ZetaFactory(Field *fld);

private:
    GameObject *createUnit(UnitClass _class, UnitDevotion devotion, int x, int y) override;

};


#endif //PROJ_ZETAFACTORY_H
