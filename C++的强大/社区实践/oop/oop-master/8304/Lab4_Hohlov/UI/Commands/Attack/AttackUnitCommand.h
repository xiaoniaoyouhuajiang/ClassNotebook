
#ifndef UNTITLED13_ATTACKUNITCOMMAND_H
#define UNTITLED13_ATTACKUNITCOMMAND_H

#include "../Command.h"

class AttackUnitCommand: public Command{

private:

    Point from;
    Point to;

public:

    AttackUnitCommand(Point from, Point to): from(from), to(to){}
    void execute(GameInfo &gameInfo, GameField &gameField) override{

        auto object1 = gameField.getCell(from)->getObject();
        auto object2 = gameField.getCell(to)->getObject();
        if (object1 && object1->getType() == ObjectType::UNIT && object1 && object1->getType() == ObjectType::UNIT) {
            auto unit1 = dynamic_cast<Unit *>(object1);
            auto unit2 = dynamic_cast<Unit *>(object2);
            unit1->attack(*unit2);
        } else
            std::cout << "Impossible attack" << std::endl;

    }

};

class AttackUnitCommandHandler: public CommandHandler {

public:

    bool canHandle(std::vector<std::string> &cmd) override{

        return cmd.size() == 5 && cmd[0] == "unit";

    }

    CommandPtr handle(std::vector<std::string> &cmd) override{

        if (canHandle(cmd)){

            int x1 = std::stoi(cmd[1]);
            int y1 = std::stoi(cmd[2]);
            int x2 = std::stoi(cmd[3]);
            int y2 = std::stoi(cmd[4]);
            Point from(x1, y1);
            Point to(x2, y2);
            return CommandPtr(new AttackUnitCommand(from, to));

        }

        if (next) return next->handle(cmd);
        return std::make_unique<Command>();

    }

};


#endif //UNTITLED13_ATTACKUNITCOMMAND_H
