//
// Created by anton on 6/1/20.
//

#ifndef OOPROJECT_GAMELOOP_H
#define OOPROJECT_GAMELOOP_H

#include <memory>

#include "Command/Sender/ISender.h"
#include "Facade/FacadeReciever.h"


class GameLoop{
private:
    //game:Game singleton
    std::shared_ptr<ISender> sender;
    std::shared_ptr<FacadeReciever>facadeReciever;
    bool syncFlag;
public:
    GameLoop(const std::shared_ptr<ISender> &sender, const std::shared_ptr<FacadeReciever> &facadeReciever);

    void loop();
    void exit();
    void restart();
};


#endif //OOPROJECT_GAMELOOP_H
