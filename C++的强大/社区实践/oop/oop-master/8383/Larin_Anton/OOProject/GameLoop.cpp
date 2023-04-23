//
// Created by anton on 6/1/20.
//

#include "GameLoop.h"

#include "Game.h"

void GameLoop::loop() {
    do{
        if(syncFlag){
            facadeReciever->turn();
        }
        syncFlag=sender->sendIfSet();
        if(!syncFlag)break;
    }while (syncFlag&&!(facadeReciever->isExitFlag()||facadeReciever->isRestartFlag()));
    if(facadeReciever->isExitFlag()){
        exit();
    }
    if(facadeReciever->isRestartFlag()){
        restart();
    }

}



void GameLoop::exit() {
    ::exit(0);
}

void GameLoop::restart() {

}

GameLoop::GameLoop(const std::shared_ptr<ISender> &sender, const std::shared_ptr<FacadeReciever> &facadeReciever)
        : sender(sender), facadeReciever(facadeReciever) {syncFlag=true;}
