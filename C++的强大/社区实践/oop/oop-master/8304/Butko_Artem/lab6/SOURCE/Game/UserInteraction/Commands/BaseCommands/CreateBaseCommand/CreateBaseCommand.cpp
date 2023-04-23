//
// Created by Artem Butko on 20/05/2020.
//

#include "CreateBaseCommand.h"

void CreateBaseCommand::Command()
{
    std::cout << "---------- BASE -----------" << std::endl;
    std::cout << "x = ";
    std::cin >> this->x;
    std::cout << "y = ";
    std::cin >> this->y;
    std::cout << "limit = ";
    std::cin >> this->unitLimit;
    std::cout << "---------------------------" << std::endl;
    field->createBase(x, y, unitLimit, 'B', 0);
}
