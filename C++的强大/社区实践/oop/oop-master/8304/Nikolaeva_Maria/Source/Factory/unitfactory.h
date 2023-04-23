#ifndef UNITFACTORY_H
#define UNITFACTORY_H

#include "Unit/unit.h"


class UnitFactory
{
public:
    virtual ~UnitFactory() = default;

    virtual Unit* createUnit(Mediator* mediator) = 0;
};

#endif // UNITFACTORY_H
