//
// Created by Artem Butko on 20/05/2020.
//

#include "AttackUnitLink.h"

void AttackUnitLink::chain(std::string command, std::string player)
{
    if (command == "/attack_unit")
    {
        ICommand* Command = new AttackUnitCommand(field, player);
        Command->Command();
    }
    else Chain::chain(command, player);
}
