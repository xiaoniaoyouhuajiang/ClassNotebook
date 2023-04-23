#ifndef UNITFACTORY_H
#define UNITFACTORY_H

#include "Units/unit.h"

class UnitFactory
{
public:
    virtual Unit* createStrong() = 0;
    virtual Unit* createWeak() = 0;

    virtual ~UnitFactory(){}
};

#endif // UNITFACTORY_H
