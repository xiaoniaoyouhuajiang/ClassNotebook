//
// Created by shenk on 18.03.2020.
//

#ifndef UNTITLED13_ATTACKCOMMAND_H
#define UNTITLED13_ATTACKCOMMAND_H


#include "../Command.h"
#include "AttackUnitCommand.h"

class AttackCommandHandler: public CommandHandler {

public:

    bool canHandle(std::vector<std::string> &cmd) override{

        return cmd.size() > 1 && cmd[0] == "attack";

    }

    CommandPtr handle(std::vector<std::string> &cmd) override{

        if (canHandle(cmd)) {

            cmd.erase(cmd.begin());

            auto handle1 = new AttackUnitCommandHandler();
            return handle1->handle(cmd);

        }

        if (next) return next->handle(cmd);
        return std::make_unique<Command>();

    }

};


#endif //UNTITLED13_ATTACKCOMMAND_H
