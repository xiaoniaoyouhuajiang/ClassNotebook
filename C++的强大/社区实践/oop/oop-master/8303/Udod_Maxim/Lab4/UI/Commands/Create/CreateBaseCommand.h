//
// Created by shenk on 16.03.2020.
//

#ifndef UNTITLED13_CREATEBASECOMMAND_H
#define UNTITLED13_CREATEBASECOMMAND_H

#include "../Command.h"
#include "../../../Armor/ArmorFlyWeight.h"
#include "../../../Armor/LeatherArmor.h"

class CreateBaseCommand: public Command {

private:

    Point basePosition;

public:

    explicit CreateBaseCommand(Point position): basePosition(position){}
    void execute(GameInfo &gameInfo, GameField &gameField) override{

        auto *base = new Base(100, *ArmorFlyWeight::getFlyWeight<LeatherArmor>());
        if (gameInfo.setNowPlayerBase(base)) {
            gameField.addBase(base, basePosition);
            game::log << "Command create base" << game::logend;
        } else
            game::log << "This player already has base" << game::logend;

    }

};

class CreateBaseCommandHandler: public CommandHandler{

public:

    bool canHandle(std::vector<std::string> &cmd) override{

        return cmd.size() == 3 && cmd[0] == "base";

    }

    CommandPtr handle(std::vector<std::string> &cmd) override {

        if (canHandle(cmd)){

            int x = std::stoi(cmd[1]);
            int y = std::stoi(cmd[2]);
            Point basePosition(x, y);
            return CommandPtr(new CreateBaseCommand(basePosition));

        }

        if (next) return next->handle(cmd);
        return std::make_unique<Command>();

    }
};


#endif //UNTITLED13_CREATEBASECOMMAND_H
