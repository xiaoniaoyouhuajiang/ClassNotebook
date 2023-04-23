#ifndef DWARFFACTORY_H
#define DWARFFACTORY_H

#include "Factory/unitfactory.h"

#include "Unit/dwarf.h"


class DwarfFactory : public UnitFactory
{
public:
    Unit* createUnit(Mediator* mediator) override;
};

#endif // DWARFFACTORY_H
