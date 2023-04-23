//
// Created by vlad on 01.06.2020.
//

#ifndef UNTITLED_LIGHTARMY_H
#define UNTITLED_LIGHTARMY_H
#include "Infantry.h"
#include "Cavalry.h"
#include "Archers.h"
#include <iostream>

class LightArcher:public Archers {
public:
    int x;
    int y;
    char type;
    int health;
public:
    LightArcher();
    int MoveUnits(int, int);
    int AttackUnits(char** , char );
    void getDamage(int);
private:
    int attack;
    int armor;
};

class LightInfantry:public Infantry {
public:
    int x;
    int y;
    char type;
    int health;
public:
    LightInfantry();
    int MoveUnits(int, int);
    int AttackUnits(char** , char );
    void getDamage(int);
private:
    int attack;
    int armor;
};

class LightCavalry:public Cavalry {
public:
    int x;
    int y;
    char type;
    int health;
public:
    LightCavalry();
    int MoveUnits(int, int);
    int AttackUnits(char** , char );
    void getDamage(int);
private:
    int attack;
    int armor;
};
#endif //UNTITLED_LIGHTARMY_H
