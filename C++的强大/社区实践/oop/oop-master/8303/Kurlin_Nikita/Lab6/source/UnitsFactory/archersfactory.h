#ifndef ARCHERSFACTORY_H
#define ARCHERSFACTORY_H

#include "unitfactory.h"
#include "Units/Archers/flatbow.h"
#include "Units/Archers/longbow.h"

class ArchersFactory : public UnitFactory
{
public:
   Longbow* createStrong() override
   {
       return new Longbow();
   }
   Flatbow* createWeak() override
   {
       return new Flatbow();
   }
};

#endif // ARCHERSFACTORY_H


