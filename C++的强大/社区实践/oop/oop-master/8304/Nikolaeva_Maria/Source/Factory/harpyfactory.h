#ifndef HARPYFACTORY_H
#define HARPYFACTORY_H

#include "Factory/unitfactory.h"

#include "Unit/harpy.h"


class HarpyFactory : public UnitFactory
{
public:
    Unit* createUnit(Mediator* mediator) override;
};

#endif // HARPYFACTORY_H
