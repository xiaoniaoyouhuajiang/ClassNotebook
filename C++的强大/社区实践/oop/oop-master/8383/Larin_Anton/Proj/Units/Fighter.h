//
// Created by anton on 2/12/20.
//

#ifndef PROJ_FIGHTER_H
#define PROJ_FIGHTER_H

#include "../GameObject.h"

class Fighter : public GameObject {
private:
    bool allyPowered;
    bool enemyPowered;
public:
    Fighter(Field *fld, int x, int y, int health, UnitDevotion devotion, bool active, bool allyPowered,
            bool enemyPowered);

    virtual bool isAllyPowered() const;

    virtual void setAllyPowered(bool allyPowered);

    virtual bool isEnemyPowered() const;

    virtual void setEnemyPowered(bool enemyPowered);

    virtual bool isValidStep(int x, int y) = 0;

    virtual bool step(int x, int y) = 0;
};


#endif //PROJ_FIGHTER_H
