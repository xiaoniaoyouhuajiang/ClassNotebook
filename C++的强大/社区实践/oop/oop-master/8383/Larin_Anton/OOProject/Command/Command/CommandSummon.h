//
// Created by anton on 5/31/20.
//

#ifndef OOPROJECT_COMMANDSUMMON_H
#define OOPROJECT_COMMANDSUMMON_H

#include "AbstractCommand.h"

#include "../../Stats.h"

struct CommandSummon: public AbstractCommand{
    CommandSummon(const std::weak_ptr<Actor> &sender, UnitClass unitClass, int x, int y)
            : AbstractCommand(sender, CommandType::CommandSummon), unitClass(unitClass), x(x), y(y) {}

    UnitClass unitClass;
    int x;
    int y;
};


#endif //OOPROJECT_COMMANDSUMMON_H
