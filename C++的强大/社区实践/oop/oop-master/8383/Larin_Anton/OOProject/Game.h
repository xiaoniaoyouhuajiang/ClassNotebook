//
// Created by anton on 5/9/20.
//

#ifndef OOPROJECT_GAME_H
#define OOPROJECT_GAME_H

#include <iostream>
#include <memory>
#include <utility>
#include <random>

#include "Field.h"
#include "Factory/CommonFactory.h"
#include "Mediator.h"
#include "Command/Sender/Sender.h"
#include "Command/Handler/everything.h"
#include "Facade/Composer.h"
#include "Actor/CLI.h"
#include "Actor/AI.h"
#include "GameLoop.h"
#include "Logger/everything.h"
#include "GameRules.h"

 
class Game {

public:
    static Game* instance;
    static Game &getInstance();
    static GameRules gameRules;
private:
    WinCondition winCondition;

public:
    static void setGameRules(const GameRules &gameRules);

private:

    std::shared_ptr<Field> field;
    //Field* field;

    std::shared_ptr<CommonFactory> factory;
    //CommonFactory* factory;

    std::shared_ptr<Mediator> mediator;
    //Mediator* mediator;

    //Handlers
    std::vector<std::shared_ptr<AbstractHandler>> commandHandlers;

    std::shared_ptr<Sender> sender;
    std::shared_ptr<FacadeReciever> facadeReciever;
    std::shared_ptr<Composer> composerA;
    std::shared_ptr<Composer> composerB;

    std::shared_ptr<Actor> actorA;
    std::shared_ptr<Actor> actorB;

    std::shared_ptr<GameLoop> gameLoop;

    std::shared_ptr<AbstractLogger> logger;

    int width;
    int height;

    Game();
public:

    //Game(const std::shared_ptr<Field> &field);

    void initField(std::pair<int, int> initAPos, std::pair<int, int> initBPos);

    void initHandlers();

     



    void demo();


    void setNoLogger();

    void setConsoleLoger();

    void setFileLogger(std::string fileName);
};


#endif //OOPROJECT_GAME_H
