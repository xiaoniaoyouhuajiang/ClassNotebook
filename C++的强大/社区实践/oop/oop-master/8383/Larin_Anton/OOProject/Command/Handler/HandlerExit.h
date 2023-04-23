//
// Created by anton on 5/31/20.
//

#ifndef OOPROJECT_HANDLEREXIT_H
#define OOPROJECT_HANDLEREXIT_H

#include <vector>
#include "AbstractHandler.h"

#include "../Command/CommandExit.h"

class HandlerExit: public AbstractHandler {
public:

    HandlerExit(const std::weak_ptr<FacadeReciever> &facadeReciever);

    bool process(std::unique_ptr<AbstractCommand> command) override;


};


#endif //OOPROJECT_HANDLEREXIT_H
