//
// Created by Artem Butko on 20/05/2020.
//

#include "MoveUnitCommand.h"

void MoveUnitCommand::Command()
{
    std::cout << "-------- MOVE UNIT --------" << std::endl;
    std::cout << "from x = ";
    std::cin >> x;
    std::cout << "from y = ";
    std::cin >> y;
    std::cout << "to x = ";
    std::cin >> i;
    std::cout << "to y = ";
    std::cin >> j;
    std::cout << "---------------------------" << std::endl;
    field->moveObject(x, y, i, j);
}
