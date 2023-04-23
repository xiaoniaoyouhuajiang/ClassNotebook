//
// Created by anton on 2/22/20.
//

#ifndef PROJ_ALPHAFACTORY_H
#define PROJ_ALPHAFACTORY_H

#include "UnitFactory.h"

//class CommonFactory;

class AlphaFactory : UnitFactory {
    friend class CommonFactory;

public:

    AlphaFactory(Field *fld);

private:

    virtual GameObject *createUnit(UnitClass _class, UnitDevotion devotion, int x, int y) override;

};


#endif //PROJ_ALPHAFACTORY_H
