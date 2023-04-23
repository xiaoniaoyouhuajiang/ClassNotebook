//
// Created by anton on 5/31/20.
//

#ifndef OOPROJECT_COMMANDSELECT_H
#define OOPROJECT_COMMANDSELECT_H

#include "AbstractCommand.h"

struct CommandSelect:public AbstractCommand {
    CommandSelect(const std::weak_ptr<Actor> &sender, bool ab, int x, int y) : AbstractCommand(
            sender, CommandType::CommandSelect), AB(ab), x(x), y(y) {}

    bool AB;
    int x;
    int y;

};


#endif //OOPROJECT_COMMANDSELECT_H
