#ifndef LABOOP_MOVEUNITCOMMAND_HPP
#define LABOOP_MOVEUNITCOMMAND_HPP

#include "Command.hpp"

class MoveUnitCommand : public Command{
public:
    void execute(GameField *gameField, Base *base, LogProxy *logger) final {
        int x1, y1;
        std::cout << "Units coordinate:\nx:";
        std::cin >> x1;
        std::cout << "y:";
        std::cin >> y1;
        if (x1 < 0 || y1 < 0 || x1 > gameField->getWidth()-1 || y1 > gameField->getHeight() -1){
            std::cout << "Incorrect coordinates." << std::endl; return;
        }
        int x2, y2;
        std::cout << "New coordinate:\nx:";
        std::cin >> x2;
        std::cout << "y:";
        std::cin >> y2;
        if (x2 < 0 || y2 < 0 || x2 > gameField->getWidth()-1 || y2 > gameField->getHeight() -1){
            std::cout << "Incorrect coordinates." << std::endl; return;
        }
        gameField->moveUnit(x1, y1, x2, y2, base);
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


#endif //LABOOP_MOVEUNITCOMMAND_HPP
