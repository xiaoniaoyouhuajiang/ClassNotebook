#ifndef WEAPON_H
#define WEAPON_H
#include "neutralobject.h"

class Weapon
{
public:
    virtual ~Weapon(){}
    virtual void use(Unit*) const = 0;
};

class ArcherWeapon : public Weapon
{
    void use(Unit* unit) const override
    {
        unit->attackAdd(25);
    }
};

class CavalryWeapon : public Weapon
{
    void use(Unit* unit) const override
    {
        unit->attackAdd(5);
    }
};

class InfantryWeapon : public Weapon
{
    void use(Unit* unit) const override
    {
        unit->attackAdd(10);
    }
};

class GetWeapon : public NeutralObject
{
private:
    const Weapon* weapon;

public:
    GetWeapon(){}
    GetWeapon(Weapon* w) : weapon(w) {}
    void operator== (Unit* unit){
        weapon->use(unit);
    }
};
#endif // WEAPON_H
