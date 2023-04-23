//
// Created by shenk on 16.04.2020.
//

#ifndef UNTITLED13_NEWGAMECOMMAND_H
#define UNTITLED13_NEWGAMECOMMAND_H

#include "../Command.h"

class NewGameCommand: public Command {

public:

    explicit NewGameCommand(){}
    void execute(GameInfo &gameInfo) override{
        gameInfo.newGame();
    }

};

class NewGameCommandHandler: public CommandHandler {

public:

    bool canHandle(std::vector<std::string> &cmd) override{
        return cmd.size() == 1 && cmd[0] == "game";
    }

    CommandPtr handle(std::vector<std::string> &cmd) override{

        if (canHandle(cmd)){
            return CommandPtr(new NewGameCommand());
        }

        if (next) return next->handle(cmd);
        return std::make_unique<Command>();

    }

};

#endif //UNTITLED13_NEWGAMECOMMAND_H
