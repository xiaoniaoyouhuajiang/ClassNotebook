#ifndef MEDICINE_H
#define MEDICINE_H
#include "neutralobject.h"

class Medicine
{
public:
    virtual ~Medicine(){}
    virtual void use(Unit*) const = 0;
};

class ArcherMedicine : public Medicine
{
    void use(Unit* unit) const override
    {
        unit->healthAdd(5);
    }
};

class CavalryMedicine : public Medicine
{
    void use(Unit* unit) const override
    {
        unit->healthAdd(15);
    }
};

class InfantryMedicine : public Medicine
{
    void use(Unit* unit) const override
    {
        unit->healthAdd(10);
    }
};

class GetMedicine : public NeutralObject
{
private:
    const Medicine* medicine;

public:
    GetMedicine(){}
    GetMedicine(Medicine* m) : medicine(m) {}
    void operator== (Unit* unit){
        medicine->use(unit);
    }
};

#endif // MEDICINE_H
