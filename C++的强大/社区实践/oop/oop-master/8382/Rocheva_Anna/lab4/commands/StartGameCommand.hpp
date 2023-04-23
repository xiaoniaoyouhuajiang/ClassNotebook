#ifndef LABOOP_STARTGAMECOMMAND_HPP
#define LABOOP_STARTGAMECOMMAND_HPP

#include "Command.hpp"

class StartGameCommand : public Command{
public:
    void execute(GameField *gameField, Base *base, LogProxy *logger) final{
        int widht, height;
        std::cout << "Width:" << std::endl;
        std::cin >> widht;
        std::cout << "Height:" << std::endl;
        std::cin >> height;
        if (widht <= 0){
            std::cout << "Incorrect width" << std::endl; return;
        }
        if (height <= 0){
            std::cout << "Incorrect height" << std::endl; return;
        }
        gameField->setSize(widht, height);
        logger->setLog("The field with a width = " + std::to_string(widht) + " and a height = " + std::to_string(height) + " was created.");
        logger->print();
        gameField->setBase(widht/2, height/2);
        logger->setLog("The base is set in a cell (" + std::to_string(widht/2) + "," + std::to_string(height/2) + ").");
        logger->print();
    }
};


#endif //LABOOP_STARTGAMECOMMAND_HPP
