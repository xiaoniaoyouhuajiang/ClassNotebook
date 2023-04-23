//
// Created by shenk on 18.03.2020.
//

#ifndef UNTITLED13_GAMEFACADE_H
#define UNTITLED13_GAMEFACADE_H

#include <sstream>
#include "GameInfo.h"
#include "UI/Commands/Command.h"
#include "UI/Commands/Attack/AttackCommand.h"
#include "UI/Commands/Create/CreateCommand.h"
#include "UI/Commands/Move/MoveCommand.h"
#include "UI/Commands/Show/ShowCommand.h"

class GameFacade: public GameInfo {

private:

    AttackCommandHandler *attackHandler;
    CreateCommandHandler *createHandler;
    MoveCommandHandler *moveHandler;
    ShowCommandHandler *showHandler;

public:

    GameFacade(int playersCount, int fieldWidth, int fieldHeight): GameInfo(playersCount, fieldWidth, fieldWidth){

        attackHandler = new AttackCommandHandler();
        createHandler = new CreateCommandHandler();
        moveHandler = new MoveCommandHandler();
        showHandler = new ShowCommandHandler();

        attackHandler->setNext(createHandler);
        createHandler->setNext(moveHandler);
        moveHandler->setNext(showHandler);

    }
    void nextTurn(){

        std::string commandString;
        std::getline(std::cin, commandString);

        std::vector <std::string> commandSplitted;
        std::stringstream ss(commandString);
        std::string commandWord;
        while (ss >> commandWord)
            commandSplitted.push_back(commandWord);


        CommandPtr command = attackHandler->handle(commandSplitted);
        command->execute(*this, gameField);

        nextUser();

    }

    void nextUser(){

        nowPlayerIndex++;
        if (nowPlayerIndex >= playersBases.size())
            nowPlayerIndex = 0;

    }

    friend std::ostream &operator<<(std::ostream &stream, const GameFacade &game){

        stream << "Now player: " << game.nowPlayerIndex << std::endl;
        stream << game.gameField << std::endl;
        return stream;

    }

};


#endif //UNTITLED13_GAMEFACADE_H
