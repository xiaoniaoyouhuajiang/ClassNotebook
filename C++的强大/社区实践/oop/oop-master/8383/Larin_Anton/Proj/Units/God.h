//
// Created by anton on 2/12/20.
//

#ifndef PROJ_GOD_H
#define PROJ_GOD_H

#include "../GameObject.h"

class God : public GameObject {
private:

public:
    God(Field *fld, int x, int y, int health, UnitDevotion devotion, bool active);

    virtual void deathEvent() = 0;

    virtual void summon(Direction dir);

    virtual wchar_t toChar() = 0;

    virtual bool isValidStep(int x, int y) = 0;

    virtual bool step(int x, int y) = 0;
};


#endif //PROJ_GOD_H
