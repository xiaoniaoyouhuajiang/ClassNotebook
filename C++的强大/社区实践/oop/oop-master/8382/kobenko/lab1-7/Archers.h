//
// Created by vlad on 01.06.2020.
//

#ifndef UNTITLED_ARCHERS_H
#define UNTITLED_ARCHERS_H
#include "Units.h"

class Archers: Units {
public:
    Archers() = default;
    virtual int MoveUnits(int , int ) = 0;
    virtual int AttackUnits(char** , char ) = 0;
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


#endif //UNTITLED_ARCHERS_H
