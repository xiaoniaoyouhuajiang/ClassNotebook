//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_UNITINTERFACE_H
#define GAME_UNITINTERFACE_H

class Unit;

class UnitInterface {
public:
    virtual void attack(Unit *unit) = 0;
};

#endif //GAME_UNITINTERFACE_H
