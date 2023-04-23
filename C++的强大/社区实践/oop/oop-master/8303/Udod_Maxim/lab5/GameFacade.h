//
// Created by shenk on 18.03.2020.
//

#ifndef UNTITLED13_GAMEFACADE_H
#define UNTITLED13_GAMEFACADE_H

#include <sstream>
#include "GameInfo.h"
#include "UI/MainCommandInterpreter.h"

class GameFacade: public GameInfo {

private:

    MainCommandInterpreter interpreter;

public:

    GameFacade(int playersCount, int fieldWidth, int fieldHeight): GameInfo(playersCount, fieldWidth, fieldWidth){}

    void nextTurn(){

        std::string commandString;
        std::getline(std::cin, commandString);

        CommandPtr command = interpreter.handle(commandString);
        command->execute(*this);
        history.push_back(command->getMemento());

        nextUser();

    }

    friend std::ostream &operator<<(std::ostream &stream, const GameFacade &game){

        stream << "Now player: " << game.nowPlayerIndex << std::endl;
        stream << game.gameField << std::endl;
        return stream;

    }

};


#endif //UNTITLED13_GAMEFACADE_H
