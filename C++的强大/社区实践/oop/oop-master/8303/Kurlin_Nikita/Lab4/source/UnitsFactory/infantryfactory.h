#ifndef INFANTRYFACTORY_H
#define INFANTRYFACTORY_H

#include "unitfactory.h"
#include "Units/Infantry/spearman.h"
#include "Units/Infantry/swordsman.h"

class InfantryFactory : public UnitFactory
{
public:
    Swordsman* createStrong() override
    {
        return new Swordsman();
    }
    Spearman* createWeak() override
    {
        return new Spearman();
    }
};

#endif // INFANTRYFACTORY_H
