#ifndef LABOOP_ATTACKUNITCOMMAND_HPP
#define LABOOP_ATTACKUNITCOMMAND_HPP

#include "Command.hpp"

class AttackUnitCommand : Command{
public:
    void execute(GameField *gameField) final {
        int x1, y1;
        std::cout << "Attacking unit coordinates:\nx:";
        std::cin >> x1;
        std::cout << "y:";
        std::cin >> y1;
        if (x1 < 0 || y1 < 0 || x1 > gameField->getWidth()-1 || y1 > gameField->getHeight() -1){
            std::cout << "Incorrect coordinates." << std::endl; return;
        }
        int x2, y2;
        std::cout << "Coordinates of unit to attack:\nx:";
        std::cin >> x2;
        std::cout << "y:";
        std::cin >> y2;
        if (x2 < 0 || y2 < 0 || x2 > gameField->getWidth()-1 || y2 > gameField->getHeight() -1){
            std::cout << "Incorrect coordinates." << std::endl; return;
        }
        gameField->attackUnit(x1, y1, x2, y2);
    }
};


#endif //LABOOP_ATTACKUNITCOMMAND_HPP
