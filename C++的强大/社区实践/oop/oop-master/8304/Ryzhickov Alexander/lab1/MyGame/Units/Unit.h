#ifndef MYGAME_UNIT_H

#define MYGAME_UNIT_H


#include "UnitInterface.h"
#include "../HelpersClasses/Position.h"
#include "../Trappings/Weapons/Weapon.h"
#include "../Trappings/Armors/Armor.h"
class Base;

class Unit : public UnitInterface {
protected:
    Position *unitPosition;
    Weapon *unitWeapon;
    Armor *unitArmor;
    int health;
    int armor;
    int damage;
    int moves;
    int numerInArmy;
    Base *base;


public:
    Position *getPosition() const;
    int getMoves() const;
    void setNumerInArmy(int numerInArmy);
    int getNumerInArmy() const;

protected:
    void setHealth(int health);

    void setArmor(int armor);

    void setDamage(int damage);

    void setMoves(int moves);

public:
    Unit(int startX, int startY, Weapon*unitWeapon, Armor *unitArmor);
    Unit();


    ~Unit();

    int getHealth() const;

    int getArmor() const;

    int getDamage() const;

    int* getArmorForGenerator();
    int* getHealthForGenerator();

   // void handleEvent(const Base& ref);

    void add(Base *ref);
    void setNewPosition(int newX, int newY);


};

#endif //MYGAME_UNIT_H
