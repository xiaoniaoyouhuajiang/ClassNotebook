#ifndef LIVESHIELDFACTORY_H
#define LIVESHIELDFACTORY_H

#include "Factory/unitfactory.h"

#include "Unit/liveshield.h"


class LiveShieldFactory : public UnitFactory
{
public:
    Unit* createUnit(Mediator* mediator) override;
};

#endif // LIVESHIELDFACTORY_H
