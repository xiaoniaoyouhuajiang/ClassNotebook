//
// Created by anton on 5/31/20.
//

#ifndef OOPROJECT_COMMANDINTERACT_H
#define OOPROJECT_COMMANDINTERACT_H

#include "AbstractCommand.h"

struct CommandInteract: public AbstractCommand {
    CommandInteract(const std::weak_ptr<Actor> &sender, bool actStep) : AbstractCommand(sender,
                                                                                        CommandType::CommandInteract),
                                                                        actStep(actStep) {}

    bool actStep;
};


#endif //OOPROJECT_COMMANDINTERACT_H
