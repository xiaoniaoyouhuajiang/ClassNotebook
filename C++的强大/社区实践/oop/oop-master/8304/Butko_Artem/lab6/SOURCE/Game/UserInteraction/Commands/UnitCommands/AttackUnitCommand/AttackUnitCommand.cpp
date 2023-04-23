//
// Created by Artem Butko on 20/05/2020.
//

#include "AttackUnitCommand.h"

void AttackUnitCommand::Command()
{
    std::cout << "-------- ATTACK --------" << std::endl;
    std::cout << "from object on x  = ";
    std::cin >> x;
    std::cout << "from object on y  = ";
    std::cin >> y;
    if (field->field[x][y].object == nullptr || field->field[x][y].object->baseID != player[0])
    {
        std::cout << "WRONG MOVE" << std::endl;
        return;
    }
    else
    {
        std::cout << "to object on x = ";
        std::cin >> i;
        std::cout << "to object on y = ";
        std::cin >> j;
        std::cout << "---------------------------" << std::endl;
        if (field->field[i][j].object == nullptr) return;
        if (player == "B" && field->field[i][j].isBrightView) field->makeDamage(x, y, i, j);
        else if (player == "D" && field->field[i][j].isDarkView) field->makeDamage(x, y, i, j);
        else if (player == "U" && field->field[i][j].isUndeadView) field->makeDamage(x, y, i, j);
        else return;
    }
}
