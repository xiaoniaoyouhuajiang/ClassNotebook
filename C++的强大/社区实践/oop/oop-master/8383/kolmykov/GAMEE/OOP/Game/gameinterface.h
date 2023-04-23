#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include "UnitType.h"


class GameInterface {
public:
    virtual void create(int xT, int xU, UnitType type) = 0;
    virtual void endStep() = 0;
};


#endif // GAMEINTERFACE_H
