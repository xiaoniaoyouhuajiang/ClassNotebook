#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include "concrete_units_classes.h"

class AbstractUnitFactory
{
public:
    virtual ~AbstractUnitFactory() = default;
    virtual IInfantry* createInfantry(unsigned int possessorId) const = 0;
    virtual ICavalry* createCavalry(unsigned int possessorId) const = 0;
    virtual IArcher* createArcher(unsigned int possessorId) const = 0;
};


class CritDealersFactory : public AbstractUnitFactory {
public:
    IInfantry* createInfantry(unsigned int possessorId) const override { return new CritInfantry(possessorId); }
    ICavalry* createCavalry(unsigned int possessorId) const override { return new CritCavalry(possessorId); }
    IArcher* createArcher(unsigned int possessorId) const override { return new CritArcher(possessorId); }
};

class AbsorbersFactory : public AbstractUnitFactory {
public:
    IInfantry* createInfantry(unsigned int possessorId) const override { return new AbsorbInfantry(possessorId); }
    ICavalry* createCavalry(unsigned int possessorId) const override { return new AbsorbCavalry(possessorId); }
    IArcher* createArcher(unsigned int possessorId) const override { return new AbsorbArcher(possessorId); }
};

#endif // ABSTRACTFACTORY_H
