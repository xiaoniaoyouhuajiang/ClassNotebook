

#ifndef UNTITLED13_MOVEUNITCOMMAND_H
#define UNTITLED13_MOVEUNITCOMMAND_H


#include "../Command.h"

class MoveUnitCommand: public Command {

private:

    Point from;
    Point to;

public:

    MoveUnitCommand(Point from, Point to): from(from), to(to){}
    virtual void execute(GameInfo &gameInfo, GameField &gameField){

        auto object1 = gameField.getCell(from)->getObject();
        if (object1 && object1->getType() == ObjectType::UNIT){
            auto unit1 = dynamic_cast<Unit *>(object1);
            unit1->move(to);
        } else
            std::cout << "No unit on this cell" << std::endl;

    }

};

class MoveUnitCommandHandler: public CommandHandler {

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
            return CommandPtr(new MoveUnitCommand(from, to));

        }

        if (next) return next->handle(cmd);
        return std::make_unique<Command>();

    }

};


#endif //UNTITLED13_MOVEUNITCOMMAND_H
