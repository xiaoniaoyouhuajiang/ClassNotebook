#ifndef CAVALRYFACTORY_H
#define CAVALRYFACTORY_H

#include "unitfactory.h"
#include "Units/Cavalry/dragoon.h"
#include "Units/Cavalry/hussar.h"

class CavalryFactory : public UnitFactory
{
public:
    Dragoon* createStrong() override
    {
        return new Dragoon();
    }
    Hussar* createWeak() override
    {
        return new Hussar();
    }
};

#endif // CAVALRYFACTORY_H
