//
// Created by anton on 5/31/20.
//

#ifndef OOPROJECT_COMMANDEXIT_H
#define OOPROJECT_COMMANDEXIT_H

#include "AbstractCommand.h"

struct CommandExit: public AbstractCommand {
    CommandExit(const std::weak_ptr<Actor> &sender) : AbstractCommand(sender,
                                                                      CommandType::CommandExit) {}

};


#endif //OOPROJECT_COMMANDEXIT_H
