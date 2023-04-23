//
// Created by anton on 5/31/20.
//

#ifndef OOPROJECT_ISENDER_H
#define OOPROJECT_ISENDER_H

#include <memory>

#include "../Command/AbstractCommand.h"

class ISender {
public:
    virtual void setAndSend(std::unique_ptr<AbstractCommand> command)=0;
    virtual void set(std::unique_ptr<AbstractCommand> command)=0;
    virtual bool sendIfSet()=0;
};


#endif //OOPROJECT_ISENDER_H
