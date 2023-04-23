//
// Created by shenk on 02.04.2020.
//

#ifndef UNTITLED13_LOADCOMMANDINTERPRETER_H
#define UNTITLED13_LOADCOMMANDINTERPRETER_H

#include "Commands/Command.h"

#include "Commands/Attack/AttackCommand.h"
#include "Commands/Create/CreateCommand.h"
#include "Commands/Move/MoveCommand.h"
#include "Commands/Show/ShowCommand.h"
#include "Commands/Exit/ExitCommand.h"
#include "Commands/New/NewCommand.h"

class LoadCommandInterpreter {

private:

    AttackCommandHandler *attackHandler;
    CreateCommandHandler *createHandler;
    MoveCommandHandler *moveHandler;
    ShowCommandHandler *showHandler;
    ExitCommandHandler *exitHandler;
    NewCommandHandler *newHandler;

public:

    LoadCommandInterpreter(){

        attackHandler = new AttackCommandHandler();
        createHandler = new CreateCommandHandler();
        moveHandler = new MoveCommandHandler();
        showHandler = new ShowCommandHandler();
        exitHandler = new ExitCommandHandler();
        newHandler = new NewCommandHandler();


        attackHandler->setNext(createHandler);
        createHandler->setNext(moveHandler);
        moveHandler->setNext(showHandler);
        showHandler->setNext(exitHandler);
        exitHandler->setNext(newHandler);
    }

    CommandPtr handle(std::string commandString){

        std::vector <std::string> commandSplitted;
        std::stringstream ss(commandString);
        std::string commandWord;
        while (ss >> commandWord)
            commandSplitted.push_back(commandWord);

        return attackHandler->handle(commandSplitted);

    }

    ~LoadCommandInterpreter(){

        delete attackHandler;
        delete createHandler;
        delete moveHandler;
        delete showHandler;
        delete exitHandler;

    }


};


#endif //UNTITLED13_LOADCOMMANDINTERPRETER_H
