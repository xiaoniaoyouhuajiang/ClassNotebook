//
// Created by Artem Butko on 20/05/2020.
//

#include "AttackUnitLink.h"

void AttackUnitLink::chain(std::string command)
{
    if (command == "/attack_unit")
    {
        ICommand* Command = new AttackUnitCommand(field);
        Command->Command();
    }
    else Chain::chain(command);
}
