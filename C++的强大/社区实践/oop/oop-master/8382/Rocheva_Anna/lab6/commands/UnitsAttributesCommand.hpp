#ifndef LABOOP_UNITSATTRIBUTESCOMMAND_HPP
#define LABOOP_UNITSATTRIBUTESCOMMAND_HPP

#include "Command.hpp"

class UnitsAttributesCommand : public Command{
public:
    void execute(GameField *gameField, Base *base, LogProxy *logger, Base *enemyBase) final {
        int x, y;
        std::cout << "Units coordinates:\nx:";
        std::cin >> x;
        std::cout << "y:";
        std::cin >> y;
        if (x < 0 || y < 0 || x > gameField->getWidth()-1 || y > gameField->getHeight() -1){
            std::cout << "Incorrect coordinates." << std::endl; return;
        }
        if (base->getUnit(x, y) == nullptr){
            std::cout << "It is not your unit." << std::endl;
            return;
        }
        gameField->getCell(x, y)->getUnit()->printAttributeValues();
    }
};


#endif //LABOOP_UNITSATTRIBUTESCOMMAND_HPP
