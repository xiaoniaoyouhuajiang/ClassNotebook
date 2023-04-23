//
// Created by anton on 6/1/20.
//

#include "HandlerRestart.h"

bool HandlerRestart::process(std::unique_ptr<AbstractCommand> command) {
    if(auto fr = facadeReciever.lock()){
        fr->restart();
    }else{
        assert(0);
    }
    return false;
}

HandlerRestart::HandlerRestart(const std::weak_ptr<FacadeReciever> &facadeReciever) : AbstractHandler({CommandType ::CommandRestart},
                                                                                                      facadeReciever) {}
