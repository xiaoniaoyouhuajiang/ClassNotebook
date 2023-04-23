#ifndef MEDIATOR_H
#define MEDIATOR_H

#include "gamefield.h"
#include "loggerproxy.h"

class Mediator
{
    GameField* field;

public:
    Mediator(GameField*);
    bool attack(Unit*, int, int);
    void setMediator(Unit *);
    void updateField(GameField*);
};

#endif // MEDIATOR_H
