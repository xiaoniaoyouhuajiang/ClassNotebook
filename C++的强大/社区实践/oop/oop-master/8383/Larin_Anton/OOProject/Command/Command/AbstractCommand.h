//
// Created by anton on 5/31/20.
//

#ifndef OOPROJECT_ABSTRACTCOMMAND_H
#define OOPROJECT_ABSTRACTCOMMAND_H

#include <memory>

class Actor;

enum class CommandType{
    CommandExit,
    CommandRestart,
    CommandSelect,
    CommandInteract,
    CommandSummon
};

struct AbstractCommand {
    AbstractCommand(const std::weak_ptr<Actor> &sender, CommandType commandType) : actor(sender),
                                                                                   commandType(commandType) {}

    std::weak_ptr<Actor> actor;
    CommandType commandType;
};


#endif //OOPROJECT_ABSTRACTCOMMAND_H
