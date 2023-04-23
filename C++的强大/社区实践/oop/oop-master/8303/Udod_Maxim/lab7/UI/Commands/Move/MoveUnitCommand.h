//
// Created by shenk on 16.03.2020.
//

#ifndef UNTITLED13_MOVEUNITCOMMAND_H
#define UNTITLED13_MOVEUNITCOMMAND_H

#include "../Command.h"
#include "../../../Utils/utils.h"

// move unit fromX fromY toX toY
class MoveUnitCommand: public Command {

private:

    Point from;
    Point to;

public:

    MoveUnitCommand(Point from, Point to): from(from), to(to){}
    void execute(GameInfo &gameInfo) override{

        auto object1 = gameInfo.getField().getCell(from)->getObject();
        if (object1 && object1->getType() == ObjectType::UNIT){
            auto unit1 = dynamic_cast<Unit *>(object1);
            unit1->move(to);
            game::log << "Command unite moved" << game::logend;
        } else
            game::log << "No unit on this cell" << game::logend;
    }

    CommandMemento * getMemento() const override{

        std::stringstream ss;
        ss << "move unit " << from.x << " " << from.y << " " << to.x << " " << to.y << std::endl;
        return new CommandMemento(ss.str());

    }

};

class MoveUnitCommandHandler: public CommandHandler {

public:

    bool canHandle(std::vector<std::string> &cmd) override{

        return cmd.size() == 5 && cmd[0] == "unit";

    }

    CommandPtr handle(std::vector<std::string> &cmd) override{

        if (canHandle(cmd)){

            int x1 = utils::StrToInt(cmd[1]);
            int y1 = utils::StrToInt(cmd[2]);
            int x2 = utils::StrToInt(cmd[3]);
            int y2 = utils::StrToInt(cmd[4]);
            Point from(x1, y1);
            Point to(x2, y2);
            return CommandPtr(new MoveUnitCommand(from, to));

        }

        if (next) return next->handle(cmd);
        return std::make_unique<Command>();

    }

};


#endif //UNTITLED13_MOVEUNITCOMMAND_H
