#ifndef SWORDSMANFACTORY_H
#define SWORDSMANFACTORY_H

#include "Factory/unitfactory.h"

#include "Unit/swordsman.h"


class SwordsmanFactory : public UnitFactory
{
public:
    Unit* createUnit(Mediator* mediator) override;
};

#endif // SWORDSMANFACTORY_H
