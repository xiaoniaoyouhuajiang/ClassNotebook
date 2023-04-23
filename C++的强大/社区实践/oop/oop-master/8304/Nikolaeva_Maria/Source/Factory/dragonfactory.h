#ifndef DRAGONFACTORY_H
#define DRAGONFACTORY_H

#include "Factory/unitfactory.h"

#include "Unit/dragon.h"


class DragonFactory : public UnitFactory
{
public:
    Unit* createUnit(Mediator* mediator) override;
};

#endif // DRAGONFACTORY_H
