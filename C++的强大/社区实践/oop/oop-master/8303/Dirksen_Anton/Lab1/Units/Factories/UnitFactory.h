//
// Created by mensch on 10.03.2020.
//

#ifndef OOP_LABS_UNITFACTORY_H
#define OOP_LABS_UNITFACTORY_H


#include "../Unit.h"

class UnitFactory {
public:
    virtual Unit* createCommon() = 0;
    virtual Unit* createStrong() = 0;
};


#endif //OOP_LABS_UNITFACTORY_H
