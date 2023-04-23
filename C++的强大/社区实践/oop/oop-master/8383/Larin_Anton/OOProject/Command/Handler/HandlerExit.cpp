//
// Created by anton on 5/31/20.
//

#include "HandlerExit.h"

bool HandlerExit::process(std::unique_ptr<AbstractCommand> command) {
    if(auto fr = facadeReciever.lock()){
        fr->exit();
    } else{
        assert(0);
    }
    return false;
}

HandlerExit::HandlerExit(const std::weak_ptr<FacadeReciever> &facadeReciever) : AbstractHandler({CommandType ::CommandExit},
                                                                                                facadeReciever) {}

