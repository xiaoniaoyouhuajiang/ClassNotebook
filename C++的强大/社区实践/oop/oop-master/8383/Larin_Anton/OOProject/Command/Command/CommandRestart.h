//
// Created by anton on 5/31/20.
//

#ifndef OOPROJECT_COMMANDRESTART_H
#define OOPROJECT_COMMANDRESTART_H

#include "AbstractCommand.h"

struct CommandRestart:public AbstractCommand {
    CommandRestart(const std::weak_ptr<Actor> &sender) : AbstractCommand(sender,
                                                                         CommandType::CommandRestart) {}

};


#endif //OOPROJECT_COMMANDRESTART_H
