//
// Created by shenk on 27.03.2020.
//

#ifndef UNTITLED13_EXITCOMMAND_H
#define UNTITLED13_EXITCOMMAND_H

#include "../Command.h"

class ExitCommand: public Command{

    void execute(GameInfo &gameInfo, GameField &gameField) override{

        exit(0);

    }

};

class ExitCommandHandler: public CommandHandler{

public:

    bool canHandle(std::vector<std::string> &cmd) override{

        return cmd.size() == 1 && cmd[0] == "exit";

    }

    CommandPtr handle(std::vector<std::string> &cmd) override{

        if (canHandle(cmd)){

            cmd.erase(cmd.begin());

            return CommandPtr(new ExitCommand());
        }

        if (next) return next->handle(cmd);

        return std::make_unique<Command>();

    }

};


#endif //UNTITLED13_EXITCOMMAND_H
