
#ifndef UNTITLED13_COMMAND_H
#define UNTITLED13_COMMAND_H

#include <string>
#include <memory>
#include "../../GameField/GameField.h"
#include "../../GameInfo.h"

class Command {

public:

    virtual void execute(GameInfo &gameInfo, GameField &gameField){}

};

typedef std::unique_ptr<Command> CommandPtr;

class CommandHandler{

protected:
    CommandHandler *next;

public:

    virtual CommandPtr handle(std::vector<std::string> &cmd)=0;
    virtual bool canHandle(std::vector<std::string> &cmd)=0;
    void setNext(CommandHandler *commandHandler){
        next = commandHandler;
    }

};


#endif //UNTITLED13_COMMAND_H
