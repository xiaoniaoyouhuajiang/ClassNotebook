//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_UNIT_H
#define GAME_UNIT_H


#include <string>
#include "../UnitAmunition/Weapon/Weapon.h"
#include "../UnitAmunition/Armor/Armor.h"
#include "UnitInterface.h"
#include "../Patterns/Observer.h"
#include "UnitsCharacteristics.h"

class Unit : public UnitInterface {
protected:
    Weapon *unitWeapon; // оружие
    Armor *unitArmor;   // броня
    int health;// здоровье
    int armor;     // показатель брони
    int damage;    // урон
    unsigned x;
    unsigned y;
    unsigned numerInArmy;
    Observer *observer;
    int maxHealth;
    int maxArmor;
    int attackBonus = 0;
    int *money;
public:
    int *getMoney() const;

public:
    unsigned int getAttackBonus() const;

public:
    Unit(int startX, int startY, Weapon*unitWeapon, Armor *unitArmor);

    Unit();

    ~Unit();

    int getHealth() const;

    int getArmor() const;

    int getDamage() const;

    unsigned int getX() const;

    unsigned int getY() const;

    unsigned int getNumerInArmy() const;

    int * getArmorForGenerator();

    int * getHealthForGenerator();

    void setNumerInArmy(unsigned int numerInArmy);

    void add(Observer *observer);

    void setAttackBonus(unsigned int attackBonus);

    void setX(unsigned int x);

    void setY(unsigned int y);

protected:
public:
    void setHealth(unsigned int health);

    void setMoney(int *money);

    std::string getInformationAboutUnit();

};


#endif //GAME_UNIT_H
