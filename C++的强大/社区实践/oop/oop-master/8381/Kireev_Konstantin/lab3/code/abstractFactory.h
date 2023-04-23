#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include "unitsclasses.h"

class AbstractUnitFactory
{
public:
    virtual ~AbstractUnitFactory() = default;
    virtual InfantryInterface* createInfantry(unsigned int possessorId) const = 0;
    virtual CavalryInterface* createCavalry(unsigned int possessorId) const = 0;
    virtual ArcherInterface* createArcher(unsigned int possessorId) const = 0;
};


class CritDealersFactory : public AbstractUnitFactory {
public:
    InfantryInterface* createInfantry(unsigned int possessorId) const override
    {
        return new CritInfantry(possessorId);
    }
    CavalryInterface* createCavalry(unsigned int possessorId) const override
    {
        return new CritCavalry(possessorId);
    }
    ArcherInterface* createArcher(unsigned int possessorId) const override
    {
        return new CritArcher(possessorId);
    }
};

class AbsorbersFactory : public AbstractUnitFactory {
public:
    InfantryInterface* createInfantry(unsigned int possessorId) const override
    {
        return new AbsorbInfantry(possessorId);
    }
    CavalryInterface* createCavalry(unsigned int possessorId) const override
    {
        return new AbsorbCavalry(possessorId);
    }
    ArcherInterface* createArcher(unsigned int possessorId) const override
    {
        return new AbsorbArcher(possessorId);
    }
};

#endif // ABSTRACTFACTORY_H
