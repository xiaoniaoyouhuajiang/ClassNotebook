//
// Created by Mila on 23.02.2020.
//

#ifndef UNTITLED_UNIT_H
#define UNTITLED_UNIT_H


#include "ObjectInterface.h"
#include "../Observer/Observer.h"

//class Base;

class Unit : public ObjectInterface{
protected:
    int health;
    int armor;//броня (т.е сколько раз надо ударить, чтобы здоровье начало падать)
    int  damage;// сила удара  (сколько падает брони и здоровья, когда бьешь)
    unsigned numberInArray;
public:
    unsigned int getNumberInArray() const;
    void attack(Unit* unit);
    void setNumberInArray(unsigned int numberArray);

protected:
    //unsigned x;
    //unsigned y;
    char name;
    Observer* observer;


public:
    //char name;
/*========================== МЕТОДЫ ==========================*/

    //Unit();

    //Unit(unsigned health, unsigned armor, unsigned damage);//конструктор

    char whatYouName() override = 0;
    ObjectInterface* copy() override = 0;

    int getArmor() const;

    void setArmor(unsigned armor);

    int getDamage() const;

    void setDamage(unsigned damage);

    int* getHealthForUpdate();
    int* getArmorForUpdate();
    int* getDamageForUpdate();

    int getHealth() const;

    void setHealth(int health);

    char getName() const;

    void setName(char name);
    void subscribeObserver(Observer* observer);

    //~Unit();

};


#endif //UNTITLED_UNIT_H
