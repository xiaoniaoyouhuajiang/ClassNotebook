#ifndef LABOOP_STARTGAMECOMMAND_HPP
#define LABOOP_STARTGAMECOMMAND_HPP

#include "Command.hpp"

class StartGameCommand : public Command{
public:
    void execute(GameField *gameField) final{
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
        gameField->setBase(widht/2, height/2);
    }
};


#endif //LABOOP_STARTGAMECOMMAND_HPP
