//
// Created by Mila on 23.02.2020.
//

#ifndef UNTITLED_UNIT_H
#define UNTITLED_UNIT_H


#include "ObjectInterface.h"

class Unit : public ObjectInterface{
protected:
    unsigned health;
    unsigned armor;//броня (т.е сколько раз надо ударить, чтобы здоровье начало падать)
    unsigned  damage;// сила удара  (сколько падает брони и здоровья, когда бьешь)
    char name;


public:
/*========================== МЕТОДЫ ==========================*/

    void whatYouName() override = 0;
    ObjectInterface* copy() override = 0;

    unsigned getArmor() const;

    void setArmor(unsigned armor);

    unsigned getDamage() const;

    void setDamage(unsigned damage);


    unsigned getHealth() const;

    void setHealth(unsigned health);

    char getName() const;

    void setName(char name);

};


#endif //UNTITLED_UNIT_H
