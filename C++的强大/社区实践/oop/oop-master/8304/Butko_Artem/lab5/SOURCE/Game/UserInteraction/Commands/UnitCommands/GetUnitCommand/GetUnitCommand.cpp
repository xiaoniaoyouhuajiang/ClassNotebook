//
// Created by Artem Butko on 20/05/2020.
//

#include "GetUnitCommand.h"

void GetUnitCommand::Command()
{
    if (this->field->base != nullptr)
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
        field->addObject(field->base->getUnit(this->id), this->x, this->y);
    }
    else std::cout << "ERROR: Base doesn't exist!" << std::endl;
}
