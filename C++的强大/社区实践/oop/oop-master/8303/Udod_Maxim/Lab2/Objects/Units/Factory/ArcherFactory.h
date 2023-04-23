//
// Created by shenk on 16.02.2020.
//

#ifndef UNTITLED13_ARCHERFACTORY_H
#define UNTITLED13_ARCHERFACTORY_H


#include "UnitFactory.h"
#include "../Archer/BlockBowMan.h"
#include "../Archer/CrossBowMan.h"

class ArcherFactory: UnitFactory {

public:
    BlockBowMan *createStrong(){ return new BlockBowMan(); }
    CrossBowMan *createWeack(){ return new CrossBowMan; }

};


#endif //UNTITLED13_ARCHERFACTORY_H
