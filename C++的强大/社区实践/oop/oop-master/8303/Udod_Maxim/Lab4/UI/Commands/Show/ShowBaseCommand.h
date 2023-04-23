//
// Created by shenk on 16.03.2020.
//

#ifndef UNTITLED13_SHOWBASECOMMAND_H
#define UNTITLED13_SHOWBASECOMMAND_H


#include "../Command.h"
#include "../../../Point.h"

class ShowBaseCommand: public Command {

private:

    Point basePosition;

public:

    explicit ShowBaseCommand(Point p): basePosition(p){}
    virtual void execute(GameInfo &gameInfo, GameField &gameField){

        auto object = gameField.getCell(basePosition)->getObject();
        if (object && object->getType() == ObjectType::BASE){

            auto base = dynamic_cast<Base*>(object);
            std::cout << "Base info: " << std::endl
                      << "\tHP: " << base->getHealth() << std::endl
                      << "\tArmor: " << base->getArmor() << std::endl
                      << "\tMax Objects Count: " << base->getMaxObjectsCount() << std::endl;
            game::log << "Show base command" << game::logend;

        } else{
            game::log << "Empty cell" << game::logend;
        }

    }

};

class ShowBaseCommandHandler: public CommandHandler {

public:

    bool canHandle(std::vector<std::string> &cmd) override{

        return cmd.size() == 3 && cmd[0] == "base";

    }

    CommandPtr handle(std::vector<std::string> &cmd) override{

        if (canHandle(cmd)){
            int x = std::stoi(cmd[1]);
            int y = std::stoi(cmd[2]);
            Point basePosition(x, y);
            return CommandPtr(new ShowBaseCommand(basePosition));
        }

        if (next) return next->handle(cmd);
        return std::make_unique<Command>();

    }

};


#endif //UNTITLED13_SHOWBASECOMMAND_H
