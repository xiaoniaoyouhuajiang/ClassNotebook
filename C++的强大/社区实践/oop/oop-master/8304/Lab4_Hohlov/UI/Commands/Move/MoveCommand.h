
#ifndef UNTITLED13_MOVECOMMAND_H
#define UNTITLED13_MOVECOMMAND_H

#include "../Command.h"
#include "MoveUnitCommand.h"

class MoveCommandHandler: public CommandHandler{

public:

    bool canHandle(std::vector<std::string> &cmd) override{

        return cmd.size() > 1 && cmd[0] == "move";

    }

    CommandPtr handle(std::vector<std::string> &cmd) override{

        if (canHandle(cmd)){

            cmd.erase(cmd.begin());

            auto handle1 = new MoveUnitCommandHandler();

            return handle1->handle(cmd);

        }

        if (next) return next->handle(cmd);
        return std::make_unique<Command>();

    }

};


#endif //UNTITLED13_MOVECOMMAND_H
