#ifndef OOP1_FACTORYUNIT_H
#define OOP1_FACTORYUNIT_H

#include "Unit.h"

class FactoryUnit{
    virtual Unit* createStrongUnit() = 0;
    virtual Unit* createWeakUnit() = 0;
};

#endif //OOP1_FACTORYUNIT_H
