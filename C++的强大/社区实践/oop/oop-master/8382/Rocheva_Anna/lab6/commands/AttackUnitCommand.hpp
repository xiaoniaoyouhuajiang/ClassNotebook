#ifndef LABOOP_ATTACKUNITCOMMAND_HPP
#define LABOOP_ATTACKUNITCOMMAND_HPP

#include "Command.hpp"

class AttackUnitCommand : Command{
public:
    void execute(GameField *gameField, Base *base, LogProxy *logger, Base *enemyBase) final {
        int x1, y1;
        std::cout << "Attacking unit coordinates:\nx:";
        std::cin >> x1;
        std::cout << "y:";
        std::cin >> y1;
        if (x1 < 0 || y1 < 0 || x1 > gameField->getWidth()-1 || y1 > gameField->getHeight() -1){
            std::cout << "Incorrect coordinates." << std::endl; return;
        }
        if (base->getUnit(x1, y1) == nullptr){
            std::cout << "It is not your unit." << std::endl;
            return;
        }
        int x2, y2;
        std::cout << "Coordinates of unit to attack:\nx:";
        std::cin >> x2;
        std::cout << "y:";
        std::cin >> y2;
        if (x2 < 0 || y2 < 0 || x2 > gameField->getWidth()-1 || y2 > gameField->getHeight()-1){
            std::cout << "Incorrect coordinates." << std::endl; return;
        }
        int count = 0;
        while (count < 3){
            if (abs(x1-x2) > 1 || abs(y1-y2) > 1 || (x1 == x2 && y1 == y2)){
                std::cout << "Incorrect coordinates. Enter new coordinates: " << std::endl;
                std::cout << "x:";
                std::cin >> x2;
                std::cout << "y:";
                std::cin >> y2;
                count++;
            } else {
                break;
            }
        }
        if (count == 3){
            std::cout << "Failed to find unit." << std::endl;
            return;
        }
        gameField->attackUnit(x1, y1, x2, y2, base, enemyBase);
        if (logger->getFormat() == 1) {
            auto adapter = new Adapter(gameField);
            adapter->setLogger(logger);
            adapter->setLog(gameField->getLogString());
            adapter->print();
        } else {
            logger->setLog(gameField->getLogString());
            logger->print();
        }
    }
};


#endif //LABOOP_ATTACKUNITCOMMAND_HPP
