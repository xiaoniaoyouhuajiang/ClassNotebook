#ifndef OOP1_FACADE_H
#define OOP1_FACADE_H

#include "Field.h"
#include "Mediator.h"
#include "Handler.h"

class Facade{

private:
    Field* field;
    Mediator* mediator;
    BaseHandler* baseHandler;
    BaseHandler* setBase;
    BaseHandler* noCommand;
    BaseHandler* setUnit;
    BaseHandler* moveUnit;
    BaseHandler* statusBase;
    BaseHandler* attackUnit;
    BaseHandler* switchLogMode;
    BaseHandler* save;
    BaseHandler* load;
    Logger* logger;
    Adapter* adapter;

public:
    void createGame();
    void play();

    void play(std::string commandStr);
};

#endif //OOP1_FACADE_H
