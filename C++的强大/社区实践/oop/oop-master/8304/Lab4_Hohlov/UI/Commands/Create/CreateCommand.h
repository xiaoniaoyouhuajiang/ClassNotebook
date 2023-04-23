

#ifndef UNTITLED13_CREATECOMMAND_H
#define UNTITLED13_CREATECOMMAND_H

#include "../Command.h"
#include "CreateUnitCommand.h"
#include "CreateBaseCommand.h"

class CreateCommandHandler: public CommandHandler {

public:

    bool canHandle(std::vector<std::string> &cmd) override{

        return cmd.size() > 1 && cmd[0] == "create";

    }

    CommandPtr handle(std::vector<std::string> &cmd) override{

        if (canHandle(cmd)){

            cmd.erase(cmd.begin());

            auto handle1 = new CreateUnitCommandHandler();
            auto handle2 = new CreateBaseCommandHandler();

            handle1->setNext(handle2);

            return handle1->handle(cmd);

        }

        if (next) return next->handle(cmd);
        return std::make_unique<Command>();

    }

};


#endif //UNTITLED13_CREATECOMMAND_H
