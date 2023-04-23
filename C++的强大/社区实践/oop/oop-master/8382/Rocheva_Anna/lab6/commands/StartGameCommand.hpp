#ifndef LABOOP_STARTGAMECOMMAND_HPP
#define LABOOP_STARTGAMECOMMAND_HPP

#include "Command.hpp"

class StartGameCommand : public Command{
public:
    void execute(GameField *gameField, Base *base, LogProxy *logger, Base *enemyBase) final{
        int widht, height;
        std::cout << "Width (min 3 and max 20):" << std::endl;
        std::cin >> widht;
        std::cout << "Height (min 3 ans max 20):" << std::endl;
        std::cin >> height;
        if (widht < 3){
            std::cout << "Incorrect width" << std::endl;
            logger->setLog("The field with a width = 20 and a height = 20 was created.");
            logger->print();
            return;
        }
        if (height < 3){
            std::cout << "Incorrect height" << std::endl;
            logger->setLog("The field with a width = 20 and a height = 20 was created.");
            logger->print();
            return;
        }
        gameField->setSize(widht, height);
        logger->setLog("The field with a width = " + std::to_string(widht) + " and a height = " + std::to_string(height) + " was created.");
        logger->print();
    }
};


#endif //LABOOP_STARTGAMECOMMAND_HPP
