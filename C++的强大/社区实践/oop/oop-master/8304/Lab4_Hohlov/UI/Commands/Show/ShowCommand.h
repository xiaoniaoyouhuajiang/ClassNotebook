

#ifndef UNTITLED13_SHOWCOMMAND_H
#define UNTITLED13_SHOWCOMMAND_H

#include "../Command.h"

#include <memory>
#include "ShowBaseCommand.h"
#include "ShowUnitCommand.h"

class ShowCommandHandler: public CommandHandler{

public:

    bool canHandle(std::vector<std::string> &cmd) override{

        return cmd.size() > 1 && cmd[0] == "show";

    }

    CommandPtr handle(std::vector<std::string> &cmd) override{

        if (canHandle(cmd)){

            cmd.erase(cmd.begin());

            auto handler1 = new ShowUnitCommandHandler;
            auto handler2 = new ShowBaseCommandHandler;
            handler1->setNext(handler2);

            return handler1->handle(cmd);
        }

        if (next) return next->handle(cmd);

        return std::make_unique<Command>();

    }

};

#endif //UNTITLED13_SHOWCOMMAND_H
