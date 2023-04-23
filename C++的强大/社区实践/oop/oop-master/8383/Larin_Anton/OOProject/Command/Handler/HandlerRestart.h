//
// Created by anton on 6/1/20.
//

#ifndef OOPROJECT_HANDLERRESTART_H
#define OOPROJECT_HANDLERRESTART_H

#include <vector>
#include "AbstractHandler.h"

class HandlerRestart: public AbstractHandler {
public:
    HandlerRestart(const std::weak_ptr<FacadeReciever> &facadeReciever);

    bool process(std::unique_ptr<AbstractCommand> command) override;

};


#endif //OOPROJECT_HANDLERRESTART_H
