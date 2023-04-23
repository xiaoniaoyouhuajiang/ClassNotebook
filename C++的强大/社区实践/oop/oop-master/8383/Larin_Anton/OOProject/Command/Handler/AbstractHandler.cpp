//
// Created by anton on 5/31/20.
//

#include <vector>
#include "AbstractHandler.h"

bool AbstractHandler::check(std::unique_ptr<AbstractCommand> command) {
    //assert(!nextHandler.expired());
    bool b = false;
    for(CommandType i:handleables){
        if(i==command->commandType){
            b=true;
            return process(std::move(command));
        }
    }

    if (auto ptr = nextHandler.lock()) {
        return ptr->check(std::move(command));
    }else{
        assert(!nextHandler.expired());
    }

    //return true;
}

AbstractHandler::AbstractHandler(const std::vector<CommandType> &handleables,
                                 const std::weak_ptr<FacadeReciever> &facadeReciever) : handleables(handleables),
                                                                                        facadeReciever(
                                                                                                facadeReciever) {}

void AbstractHandler::setNextHandler(const std::weak_ptr<AbstractHandler> &nextHandler) {
    AbstractHandler::nextHandler = nextHandler;
}
