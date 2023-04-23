//
// Created by vlad on 01.06.2020.
//

#ifndef UNTITLED_INFANTRY_H
#define UNTITLED_INFANTRY_H
#include "Units.h"

class Infantry:Units {
public:
    virtual int MoveUnits(int , int ) = 0;
    virtual int AttackUnits(char** , char )= 0;
    virtual void getDamage(int) =0;
public:
    int x;
    int y;
    char type;
    int health;
private:
    int attack;
    int armor;
};




#endif //UNTITLED_INFANTRY_H
