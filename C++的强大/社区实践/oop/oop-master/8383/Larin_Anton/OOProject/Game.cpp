//
// Created by anton on 5/9/20.
//

#include <utility>
#include "Game.h"
#include "Logger/LoggerProxy.h"
#include "Logger/ConsoleLoggerAdapter.h"
#include "Logger/FileLoggerAdapter.h"
#include "Logger/NoLogger.h"

/*
#include "GameObject/Unit/TheTough.h"
#include "GameObject/Entity/PitEntity.h"
#include "GameObject/Terrain/HollyTerrain.h"
*/

GameRules Game::gameRules;
 
Game* Game::instance = nullptr;
/*
 
Game &Game::getInstance() {
    if(instance== nullptr){
        instance = new Game(9,9);
    }
    return *instance;
}
*/



Game &Game::getInstance() {
    if(instance== nullptr){
        instance = new Game();
    }
    return *instance;
}



 
void Game::demo() {

    std::string s1 = "foo";
    std::string s2 = "bar";


    s2 = "foo";
    gameLoop->loop();
    return;

}

/*

Game::Game(const std::shared_ptr<Field> &field):field(field) {}
*/

Game::Game() {
    winCondition=gameRules.winCondition;

    this->width=gameRules.width;
    this->height=gameRules.height;

    field =std::make_shared<Field>(2*width*height,height,width);
    //field = new Field(2*width*height,height,width);

    factory =std::make_shared<CommonFactory>();
            //factory = new CommonFactory();
    mediator =std::make_shared<Mediator>(std::shared_ptr<Field>(field),std::shared_ptr<CommonFactory>(factory));
    //mediator = new Mediator(std::shared_ptr<Field>(field),std::shared_ptr<CommonFactory>(factory));
    factory->setMediator(std::shared_ptr<Mediator>(mediator));

    actorA = std::make_shared<CLI>("A");
    if(gameRules.multiplayer) {
        actorB = std::make_shared<CLI>("B");
    }else{
        actorB = std::make_shared<AI>("Bot");
    }
    composerA= std::make_shared<Composer>(true,actorA,mediator);//Should be two of'em
    composerB= std::make_shared<Composer>(true,actorB,mediator);//Should be two of'em
    actorA->setComposer(composerA);
    actorB->setComposer(composerB);
    facadeReciever = std::make_shared<FacadeReciever>(mediator);
    facadeReciever->init(gameRules.firstA,actorA,actorB);


    initHandlers();
    sender=std::make_shared<Sender>(commandHandlers.front());
    composerA->setSender(sender);
    composerB->setSender(sender);


    gameLoop = std::make_shared<GameLoop>(sender,facadeReciever);




    setNoLogger();

    initField(gameRules.initAPos, gameRules.initBPos);
}
 
void Game::initHandlers() {
    commandHandlers.push_back(std::make_shared<HandlerExit>(facadeReciever));
    commandHandlers.push_back(std::make_shared<HandlerRestart>(facadeReciever));
    commandHandlers.push_back(std::make_shared<HandlerStuff>(facadeReciever));
    for (int i = 0; i < commandHandlers.size() - 1; i++) {
        commandHandlers[i]->setNextHandler(commandHandlers[i + 1]);
    }
}

 
void Game::initField(std::pair<int, int> initAPos, std::pair<int, int> initBPos) {
    for(int i= 0;i<height; i++){
        for(int j = 0; j<width; j++){
            int s = (i+j)%3;
            switch (s){
             case 0:mediator->createObject(j,i,Devotion::Neuter,CommonClass::SpikyTerrain);break;
             case 1:mediator->createObject(j,i,Devotion::Neuter,CommonClass::SteepTerrain);break;
             case 2:mediator->createObject(j,i,Devotion::Neuter,CommonClass::HollyTerrain);break;
            }
        }
    }
    mediator->createObject(initAPos.first,initAPos.second,Devotion::Light,CommonClass::Base);
    //std::pair<int,int> dim = mediator->getDimensions();
    mediator->createObject(initBPos.first,initBPos.second,Devotion::Dark,CommonClass::Base);
    mediator->createObject(3,3,Devotion::Neuter,CommonClass::HealEntity);
    mediator->createObject(5,5,Devotion::Neuter,CommonClass::TrapEntity);
    mediator->createObject(4,4,Devotion::Neuter,CommonClass::PitEntity);
}

 
void Game::setConsoleLoger() {
    std::shared_ptr<LoggerProxy> lp = std::make_shared<LoggerProxy>();
    std::shared_ptr<ConsoleLoggerAdapter> cla  =std::make_shared<ConsoleLoggerAdapter>();
    lp->setAbstractLogger(cla);
    logger=lp;

    sender->setLogger(logger);
    mediator->setLogger(logger);
}

 
void Game::setFileLogger(std::string fileName) {
    std::shared_ptr<LoggerProxy> lp = std::make_shared<LoggerProxy>();
    std::shared_ptr<FileLoggerAdapter> fla  =std::make_shared<FileLoggerAdapter>(fileName);
    lp->setAbstractLogger(fla);
    logger=lp;

    sender->setLogger(logger);
    mediator->setLogger(logger);
}

 
void Game::setNoLogger() {
    std::shared_ptr<LoggerProxy> lp = std::make_shared<LoggerProxy>();
    std::shared_ptr<NoLogger> nl=std::make_shared<NoLogger>();
    lp->setAbstractLogger(nl);
    logger=lp;

    sender->setLogger(logger);
    mediator->setLogger(logger);
}

void Game::setGameRules(const GameRules &gameRules) {
    Game::gameRules = gameRules;
}


