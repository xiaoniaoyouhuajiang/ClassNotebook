//
// Created by shenk on 14.02.2020.
//

#ifndef UNTITLED13_UNIT_H
#define UNTITLED13_UNIT_H


#include "../Armor/Armor.h"
#include "../Weapon/Weapon.h"
#include "../Point.h"

class Unit {

    friend class GameField;

protected:

    Point position;

    Armor armor;
    Weapon weapon;
    int health;

    bool isOnField = false;

public:

    Unit(Unit *other);
    Unit() {}

    Point& getPosition() { return position; }
    
};


#endif //UNTITLED13_UNIT_H
