//
// Created by Artem Butko on 20/05/2020.
//

#include "GetUnitCommand.h"

void GetUnitCommand::Command()
{
    int number;
    if (player == "B") number = 0;
    else if (player == "D") number = 1;
    else number = 2;
    if (this->field->basesOnField[number]!= nullptr)
    {
        std::cout << "--------- GET UNIT --------" << std::endl;
        std::cout << "'C' - Crossbowman" << std::endl;
        std::cout << "'A' - Archer" << std::endl;
        std::cout << "'W' - Wizard" << std::endl;
        std::cout << "'M' - Mage" << std::endl;
        std::cout << "'K' - Knight" << std::endl;
        std::cout << "'S' - Spearman" << std::endl;
        std::cout << "---------------------------" << std::endl;
        std::cout << "id = ";
        std::cin >> this->id;
        std::cout << "x = ";
        std::cin >> this->x;
        std::cout << "y = " ;
        std::cin >> this->y;
        std::cout << "---------------------------" << std::endl;
        field->addObject(this->field->basesOnField[number]->getUnit(this->id), this->x, this->y);
    }
    else std::cout << "ERROR: Base doesn't exist!" << std::endl;
}
