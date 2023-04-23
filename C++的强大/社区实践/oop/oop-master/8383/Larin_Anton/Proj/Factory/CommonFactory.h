//
// Created by anton on 2/22/20.
//

#ifndef PROJ_COMMONFACTORY_H
#define PROJ_COMMONFACTORY_H

#include "../Field.h"
#include "AlphaFactory.h"
#include "BetaFactory.h"
#include "GammaFactory.h"
#include "DeltaFactory.h"
#include "EpsilonFactory.h"
#include "ZetaFactory.h"
#include "BushFactory.h"
#include "FireFactory.h"
#include "TreeFactory.h"
#include "StoneFactory.h"


class CommonFactory {
private:
    Field *fld;
    AlphaFactory *alphaFactory;
    BetaFactory *betaFactory;
    GammaFactory *gammaFactory;
    DeltaFactory *deltaFactory;
    EpsilonFactory *epsilonFactory;
    ZetaFactory *zetaFactory;
    BushFactory *bushFactory;
    FireFactory *fireFactory;
    TreeFactory *treeFactory;
    StoneFactory *stoneFactory;

public:
    CommonFactory(Field *fld);

    GameObject *createUnit(UnitClass _class, UnitDevotion devotion = UnitDevotion::NEUTER, int x = -1, int y = -1);

    virtual ~CommonFactory();
};




#endif //PROJ_COMMONFACTORY_H
