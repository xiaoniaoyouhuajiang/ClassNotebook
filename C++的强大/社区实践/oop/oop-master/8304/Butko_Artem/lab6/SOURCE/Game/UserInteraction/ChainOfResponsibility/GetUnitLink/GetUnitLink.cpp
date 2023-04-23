//
// Created by Artem Butko on 20/05/2020.
//

#include "GetUnitLink.h"

void GetUnitLink::chain(std::string command, std::string player)
{
    if (command == "/get_unit")
    {
        ICommand* Command = new GetUnitCommand(field, player);
        Command->Command();
    }
    else Chain::chain(command, player);
}
