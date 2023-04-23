//
// Created by anton on 6/1/20.
//

#ifndef OOPROJECT_HANDLERSTUFF_H
#define OOPROJECT_HANDLERSTUFF_H

#include <vector>
#include "AbstractHandler.h"

class HandlerStuff: public AbstractHandler {
public:
    HandlerStuff(const std::weak_ptr<FacadeReciever> &facadeReciever);

    bool process(std::unique_ptr<AbstractCommand> command) override;

};


#endif //OOPROJECT_HANDLERSTUFF_H
