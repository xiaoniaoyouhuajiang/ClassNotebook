
#ifndef UNTITLED13_MAINCOMMAND_H
#define UNTITLED13_MAINCOMMAND_H

#include "Command.h"
#include "Show/ShowCommand.h"
#include "Create/CreateCommand.h"
#include "Move/MoveCommand.h"
#include "Attack/AttackCommand.h"

class MainCommandHandler: public CommandHandler {

public:

    virtual CommandPtr handle(std::vector<std::string> &cmd){
        if (cmd.size() < 1){
            std::cout << "Wrong command" << std::endl;
            return CommandPtr(new Command);
        }

        std::string cmdWrd = cmd[0];
        cmd.erase(cmd.begin());
        if (cmdWrd == "show"){

            return ShowCommandHandler().handle(cmd);

        } else if (cmdWrd == "create"){

            return CreateCommandHandler().handle(cmd);

        } else if (cmdWrd == "move"){

            return MoveCommandHandler().handle(cmd);

        } else if (cmdWrd == "attack"){

            return AttackCommandHandler().handle(cmd);

        }

        return CommandPtr(new Command);
    }

};


#endif //UNTITLED13_MAINCOMMAND_H
