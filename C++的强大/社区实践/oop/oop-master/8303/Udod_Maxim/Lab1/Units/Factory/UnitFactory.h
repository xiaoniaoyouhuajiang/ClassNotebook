//
// Created by shenk on 16.02.2020.
//

#ifndef UNTITLED13_UNITFACTORY_H
#define UNTITLED13_UNITFACTORY_H


#include "../Unit.h"

class UnitFactory {

public:
    virtual Unit* createStrong()=0;
    virtual Unit* createWeack()=0;

};


#endif //UNTITLED13_UNITFACTORY_H
