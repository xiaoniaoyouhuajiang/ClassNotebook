//
// Created by shenk on 16.03.2020.
//

#ifndef UNTITLED13_NEWCOMMAND_H
#define UNTITLED13_NEWCOMMAND_H

#include "../Command.h"
#include "NewGameCommand.h"

#include <memory>

class NewCommandHandler: public CommandHandler{

public:

    bool canHandle(std::vector<std::string> &cmd) override{

        return cmd.size() > 1 && cmd[0] == "new";

    }

    CommandPtr handle(std::vector<std::string> &cmd) override{

        if (canHandle(cmd)){

            cmd.erase(cmd.begin());

            auto handler1 = new NewGameCommandHandler;

            return handler1->handle(cmd);
        }

        if (next) return next->handle(cmd);

        return std::make_unique<Command>();

    }

};

#endif //UNTITLED13_SHOWCOMMAND_H
