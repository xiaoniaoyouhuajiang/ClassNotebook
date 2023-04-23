#ifndef LABOOP_ACTIONWITHOBJECTCOMMAND_HPP
#define LABOOP_ACTIONWITHOBJECTCOMMAND_HPP

#include "Command.hpp"

class ActionWithObjectCommand : public Command{
public:
    void execute(GameField *gameField, Base *base, LogProxy *logger) final {
        std::cout << "Coordinates of cell:" << std::endl;
        int x, y;
        std::cout << "x:";
        std::cin >> x;
        std::cout << "y:";
        std::cin >> y;
        if (x < 0 || y < 0 || x > gameField->getWidth()-1 || y > gameField->getHeight() -1){
            std::cout << "Incorrect coordinates." << std::endl; return;
        }
        gameField->makeActionWithObj(x, y);
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


#endif //LABOOP_ACTIONWITHOBJECTCOMMAND_HPP
