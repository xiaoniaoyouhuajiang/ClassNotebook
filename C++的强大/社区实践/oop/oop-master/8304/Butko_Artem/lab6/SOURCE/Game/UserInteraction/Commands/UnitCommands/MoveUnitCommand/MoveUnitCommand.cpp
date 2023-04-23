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
    if (field->field[x][y].object == nullptr || field->field[x][y].object->baseID != player[0])
    {
        std::cout << "WRONG MOVE" << std::endl;
        return;
    }
    else
    {
        while(true)
        {
            std::cout << "to x = ";
            std::cin >> i;
            std::cout << "to y = ";
            std::cin >> j;
            bool isInRange = std::pow(x, 2) + std::pow(y, 2) >= std::pow(field->field[x][y].object->range.get(), 2);

            if (field->field[i][j].object == nullptr && isInRange)
            {
                field->getVision(player[0],i , j);
                break;
            }
        }
        field->moveObject(x, y, i, j);
        std::cout << "---------------------------" << std::endl;
    }

}
