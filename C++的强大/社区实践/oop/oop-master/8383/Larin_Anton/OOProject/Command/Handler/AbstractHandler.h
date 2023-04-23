//
// Created by anton on 5/31/20.
//

#ifndef OOPROJECT_ABSTRACTHANDLER_H
#define OOPROJECT_ABSTRACTHANDLER_H

#include <memory>
#include <vector>

#include "../Command/AbstractCommand.h"
#include "../../Facade/FacadeReciever.h"

template<typename TO, typename FROM>
std::unique_ptr<TO> static_unique_pointer_cast (std::unique_ptr<FROM>&& old){
    return std::unique_ptr<TO>{static_cast<TO*>(old.release())};
    //conversion: unique_ptr<FROM>->FROM*->TO*->unique_ptr<TO>
}


class AbstractHandler {
public:
    AbstractHandler(const std::vector<CommandType> &handleables, const std::weak_ptr<FacadeReciever> &facadeReciever);

private:
    std::weak_ptr<AbstractHandler> nextHandler;
protected:
    std::vector<CommandType> handleables;
    std::weak_ptr<FacadeReciever> facadeReciever;
public:

    void setNextHandler(const std::weak_ptr<AbstractHandler> &nextHandler);

    virtual bool check(std::unique_ptr<AbstractCommand> command);

    virtual bool process(std::unique_ptr<AbstractCommand> command)=0;

};


#endif //OOPROJECT_ABSTRACTHANDLER_H
