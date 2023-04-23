#ifndef ARMOR_H
#define ARMOR_H
#include "neutralobject.h"

class Armor
{
public:
    virtual ~Armor(){}
    virtual void use(Unit*) const = 0;
};

class ArcherArmor : public Armor
{
    void use(Unit* unit) const override
    {
       unit->armorAdd(80);
    }
};

class CavalryArmor : public Armor
{
    void use(Unit* unit) const override
    {
        unit->armorAdd(20);
    }
};

class InfantryArmor : public Armor
{
    void use(Unit* unit) const override
    {
        unit->armorAdd(10);
    }
};

class GetArmor : public NeutralObject
{
private:
    const Armor* armor;

public:
    GetArmor(){}
    GetArmor(Armor* a) : armor(a) {}
    void operator== (Unit* unit){
        armor->use(unit);
    }
};

#endif // ARMOR_H
