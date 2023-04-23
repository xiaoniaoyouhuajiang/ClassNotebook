//
// Created by shenk on 16.03.2020.
//

#ifndef UNTITLED13_CREATEUNITCOMMAND_H
#define UNTITLED13_CREATEUNITCOMMAND_H


#include "../Command.h"
#include "../../../Objects/Units/Infantry/SwordMan.h"
#include "../../../Objects/Units/Archer/CrossBowMan.h"
#include "../../../Objects/Units/Wizard/FireMage.h"

class CreateUnitCommand: public Command {

private:

    Point unitPosition;
    UnitType unitType;

public:

    explicit CreateUnitCommand(Point position, UnitType unitType): unitPosition(position), unitType(unitType){}
    void execute(GameInfo &gameInfo, GameField &gameField) override{

        if (!gameInfo.getNowPlayerBase()){
            std::cout << "Can't create unit without base" << std::endl;
            return;
        }

        switch (unitType) {

            case UnitType::INFANTRY:
                gameInfo.getNowPlayerBase()->createUnit<SwordMan>(unitPosition);
                break;
            case UnitType::ARCHER:
                gameInfo.getNowPlayerBase()->createUnit<CrossBowMan>(unitPosition);
                break;
            case UnitType::WIZARD:
                gameInfo.getNowPlayerBase()->createUnit<FireMage>(unitPosition);
                break;

        }

    }

};

class CreateUnitCommandHandler: public CommandHandler {

public:

    bool canHandle(std::vector<std::string> &cmd) override{

        return cmd.size() == 4 && cmd[0] == "unit";

    }

    CommandPtr handle(std::vector<std::string> &cmd) override {

        if (canHandle(cmd)){

            int x = std::stoi(cmd[1]);
            int y = std::stoi(cmd[2]);
            auto type = static_cast<UnitType>(std::stoi(cmd[3]));
            Point basePosition(x, y);
            return CommandPtr(new CreateUnitCommand(basePosition, type));

        }

        if (next) return next->handle(cmd);
        return std::make_unique<Command>();

    }

};


#endif //UNTITLED13_CREATEUNITCOMMAND_H
