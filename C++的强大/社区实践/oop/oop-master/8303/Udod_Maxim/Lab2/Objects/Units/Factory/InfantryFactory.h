//
// Created by shenk on 16.02.2020.
//

#ifndef UNTITLED13_INFANTRYFACTORY_H
#define UNTITLED13_INFANTRYFACTORY_H

#include "UnitFactory.h"
#include "../Infantry/SwordMan.h"
#include "../Infantry/SpearMan.h"

class InfantryFactory: public UnitFactory {

public:
    SwordMan *createStrong(){ return new SwordMan(); }
    SpearMan *createWeack(){ return new SpearMan(); }

};


#endif //UNTITLED13_INFANTRYFACTORY_H
