#ifndef ARCHERFACTORY_H
#define ARCHERFACTORY_H

#include "Factory/unitfactory.h"

#include "Unit/archer.h"


class ArcherFactory : public UnitFactory
{
public:
    Unit* createUnit(Mediator* mediator) override;
};

#endif // ARCHERFACTORY_H
