#ifndef FACADE_H
#define FACADE_H

#include "gamefield.h"
#include "basehandler.h"
#include "mediator.h"
#include "loggerproxy.h"
#include "logger.h"

class Facade
{
    GameField* field;
    BaseHandler* baseHandler;
    Mediator* mediator;

    //CreateBaseHandler* createBaseHandler;
    CreateUnitHandler* createUnitHandler;
    MoveUnitHandler* moveUnitHandler;
    BaseStatusHandler* baseStatusHandler;
    AttackHandler* attackHandler;
    LogOnOffHandler* logHandler;
    SaveGameHandler* saveGameHandler;
    LoadGameHandler* loadGameHandler;
    WrongCommandHandler* wrongCommandHandler;

public:
    Facade();
    void prepareGame();
    void startGame();
};

#endif // FACADE_H
