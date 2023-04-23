#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H
#include <unitsclasses.h>

class AbstractFactory //абстрактная фабрика
{
public:
    virtual ~AbstractFactory() = default;
    virtual InfantryInterface* createInfantry(Type type) const = 0;
    virtual CavalryInterface* createCavalry(Type type) const = 0;
    virtual ArcherInterface* createArcher(Type type) const = 0;
};

class CritUnitsFactory : public AbstractFactory //конкретная фабрика, поставляющая юнитов с критическим уроном
{
public:
    InfantryInterface* createInfantry(Type type) const override
    {
        return new CritInfantry(type);
    }
    CavalryInterface* createCavalry(Type type) const override
    {
        return new CritCavalry(type);
    }
    ArcherInterface* createArcher(Type type) const override
    {
        return new CritArcher(type);
    }
};

class DamageAbsorberUnitsFactory : public AbstractFactory //конкретная фабрика, поставляющая юнитов с поглощением урона
{
public:
    InfantryInterface* createInfantry(Type type) const override
    {
        return new DamageAbsorberInfantry(type);
    }
    CavalryInterface* createCavalry(Type type) const override
    {
        return new DamageAbsorberCavalry(type);
    }
    ArcherInterface* createArcher(Type type) const override
    {
        return new DamageAbsorberArcher(type);
    }
};

#endif // ABSTRACTFACTORY_H
