//
// Created by shenk on 18.03.2020.
//

#ifndef UNTITLED13_GAMEFACADE_H
#define UNTITLED13_GAMEFACADE_H

#include <sstream>
#include "GameInfo.h"
#include "UI/MainCommandInterpreter.h"
#include "Exceptions/DoublePlacingOnFieldException.h"
#include "Exceptions/GameFieldOutOfRangeException.h"
#include "Exceptions/ImpossibleMoveException.h"

template<typename Rule, int playersCount>
class GameFacade: public GameInfo {

private:

    MainCommandInterpreter interpreter;
    GameFacade(int fieldWidth, int fieldHeight): GameInfo(playersCount, fieldWidth, fieldWidth, new Rule){}
    Rule rule;

public:

    static GameFacade& instance(){
        Rule rule;
        static GameFacade singleInstance(rule.fieldWidth, rule.fieldHeight);
        return singleInstance;
    }

    void nextTurn(){

        std::string commandString;
        std::getline(std::cin, commandString);

        CommandPtr command = interpreter.handle(commandString);
        try {
            command->execute(*this);
        } catch(DoubleBasePlacingException &exception) {
            std::cout << "Player " << exception.playerIndex << " trying to place base second time." << std::endl;
        } catch (DoublePlacingOnFieldException &exception){
            std::cout << "This cell is busy by other object." << std::endl;
        } catch (GameFieldOutOfRangeException &exception){
            std::cout << "Out of range. Cell " << exception.x << " " << exception.y << " is not exist." << std::endl;
        } catch (ImpossibleMoveException &exception){
            std::cout << "Can't move to this cell. They busy by other object." << std::endl;
        } catch (InvalidFileLoaddingException &exception){
            std::cout << "Wrong file." << std::endl;
        } catch (...){
            std::cout << "Undefined error." << std::endl;
        }
        history.push_back(command->getMemento());

        nextUser();

    }

    friend std::ostream &operator<<(std::ostream &stream, const GameFacade &game){

        stream << "Now player: " << game.nowPlayerIndex << std::endl;
        stream << game.gameField << std::endl;
        return stream;

    }

    bool isOver(){

        return rule.isOver(*this);

    }

};


#endif //UNTITLED13_GAMEFACADE_H
