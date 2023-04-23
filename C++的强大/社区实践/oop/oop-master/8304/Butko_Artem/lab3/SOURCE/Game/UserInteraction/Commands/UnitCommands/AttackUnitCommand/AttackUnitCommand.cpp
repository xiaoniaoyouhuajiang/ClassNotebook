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
    std::cout << "to object on x = ";
    std::cin >> i;
    std::cout << "to object on y = ";
    std::cin >> j;
    std::cout << "---------------------------" << std::endl;
    field->makeDamage(x, y, i, j);
}
