#ifndef LABOOP_DELETEUNITCOMMAND_HPP
#define LABOOP_DELETEUNITCOMMAND_HPP

#include "Command.hpp"

class DeleteUnitCommand : public Command{
public:
    void execute(GameField *gameField) final {
        int x, y;
        std::cout << "Units coordinate:\nx:";
        std::cin >> x;
        std::cout << "y:";
        std::cin >> y;
        if (x < 0 || y < 0 || x > gameField->getWidth()-1 || y > gameField->getHeight() -1){
            std::cout << "Incorrect coordinates." << std::endl; return;
        }
        gameField->deleteUnit(x, y);
    }
};


#endif //LABOOP_DELETEUNITCOMMAND_HPP
