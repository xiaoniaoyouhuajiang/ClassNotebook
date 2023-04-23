#ifndef WEAPON_H
#define WEAPON_H

#include "neutralObj.h"

class Weapon{
public:
    virtual ~Weapon()=default;
    virtual void use(Unit& unit)=0;
};

class Sword : public Weapon{

public:
    void use(Unit &unit);
};

class Hatchet : public Weapon{

public:
    void use(Unit &unit);
};

class GetWeapon : public NeutralObj
{
private:
    Weapon* weapon;
public:
    GetWeapon(Weapon*);
    void operator +=(Unit &unit);
    ~GetWeapon();
    string characteristic();
    string getType()const;
};

#endif // WEAPON_H
