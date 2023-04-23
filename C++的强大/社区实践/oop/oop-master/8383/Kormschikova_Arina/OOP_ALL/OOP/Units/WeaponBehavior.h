

#ifndef WeaponBehavior_h
#define WeaponBehavior_h

#include "Interfaces.h"


class WeaponBehavior: public IWeaponBehavior{
public:
    int baseDamage;
    int extraRandomDamage;
    int radius;
    int againstMagicArmor;
    int againstPhysicalArmor;
    int damageСalculation( int magicResistance, int armor) override;
    int damageСalculation(int magicResistance, int armor, int againstMA, int againstPA) override;
};


class Sword: public WeaponBehavior{
public:
    Sword();
    int useWeapon(int distance, int magicResistance = 0, int armor = 0) override;
};


class Lance: public WeaponBehavior{
public:
    Lance();
    int useWeapon(int distance, int magicResistance = 0, int armor = 0) override;
};


class Dagger: public WeaponBehavior{
public:
    Dagger();
    int useWeapon(int distance, int magicResistance = 0, int armor = 0) override;
};


class Bow: public WeaponBehavior{
public:
    Bow();
    int useWeapon(int distance, int magicResistance = 0, int armor = 0) override;
};


class Staff: public WeaponBehavior{
public:
    Staff();
    int useWeapon(int distance, int magicResistance = 0, int armor = 0) override;
};


class Hands: public WeaponBehavior{
public:
    Hands();
    int useWeapon(int distance, int magicResistance = 0, int armor = 0) override;
};

#endif /* WeaponBehavior_h */
