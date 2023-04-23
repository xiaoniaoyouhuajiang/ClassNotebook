//
// Created by shenk on 02.04.2020.
//

#ifndef UNTITLED13_MAINCOMMANDINTERPRETER_H
#define UNTITLED13_MAINCOMMANDINTERPRETER_H

#include "Commands/Command.h"

#include "Commands/Attack/AttackCommand.h"
#include "Commands/Create/CreateCommand.h"
#include "Commands/Move/MoveCommand.h"
#include "Commands/Show/ShowCommand.h"
#include "Commands/Exit/ExitCommand.h"
#include "Commands/Save/SaveCommand.h"
#include "Commands/Load/LoadCommand.h"
#include "Commands/New/NewCommand.h"

class MainCommandInterpreter {

private:

    AttackCommandHandler *attackHandler;
    CreateCommandHandler *createHandler;
    MoveCommandHandler *moveHandler;
    ShowCommandHandler *showHandler;
    ExitCommandHandler *exitHandler;
    SaveCommandHandler *saveHandler;
    LoadCommandHandler *loadHandler;
    NewCommandHandler *newHandler;

public:

    MainCommandInterpreter(){

        attackHandler = new AttackCommandHandler();
        createHandler = new CreateCommandHandler();
        moveHandler = new MoveCommandHandler();
        showHandler = new ShowCommandHandler();
        exitHandler = new ExitCommandHandler();
        saveHandler = new SaveCommandHandler();
        loadHandler = new LoadCommandHandler();
        newHandler = new NewCommandHandler();

        attackHandler->setNext(createHandler);
        createHandler->setNext(moveHandler);
        moveHandler->setNext(showHandler);
        showHandler->setNext(exitHandler);
        exitHandler->setNext(saveHandler);
        saveHandler->setNext(loadHandler);
        loadHandler->setNext(newHandler);
    }

    CommandPtr handle(std::string commandString){

        std::vector <std::string> commandSplitted;
        std::stringstream ss(commandString);
        std::string commandWord;
        while (ss >> commandWord)
            commandSplitted.push_back(commandWord);

        return attackHandler->handle(commandSplitted);

    }

    ~MainCommandInterpreter(){

        delete attackHandler;
        delete createHandler;
        delete moveHandler;
        delete showHandler;
        delete exitHandler;
        delete saveHandler;

    }

};


#endif //UNTITLED13_MAINCOMMANDINTERPRETER_H
