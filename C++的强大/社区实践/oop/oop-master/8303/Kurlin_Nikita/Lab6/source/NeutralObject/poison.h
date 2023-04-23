#ifndef POISON_H
#define POISON_H
#include "neutralobject.h"

class Poison
{
public:
    virtual ~Poison(){}
    virtual void use(Unit*) const = 0;
};

class ArcherPoison : public Poison
{
    void use(Unit* unit) const override
    {
        unit->deapth();
    }
};

class CavalryPoison : public Poison
{
    void use(Unit* unit) const override
    {
        unit->healthAdd(-20);
    }
};

class InfantryPoison : public Poison
{
    void use(Unit* unit) const override
    {
        unit->healthAdd(-25);
    }
};

class DrinkPoison : public NeutralObject
{
private:
    const Poison* poison;

public:
    DrinkPoison(){}
    DrinkPoison(Poison* p) : poison(p) {}
    void operator== (Unit* unit){
        poison->use(unit);
    }
};

#endif // POISON_H
