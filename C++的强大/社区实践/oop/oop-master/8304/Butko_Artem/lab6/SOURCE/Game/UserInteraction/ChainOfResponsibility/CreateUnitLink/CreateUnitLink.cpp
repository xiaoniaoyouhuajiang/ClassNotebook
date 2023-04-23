//
// Created by Artem Butko on 20/05/2020.
//

#include "CreateUnitLink.h"

void CreateUnitLink::chain(std::string command, std::string player)
{
    if (command == "/create_unit")
    {
        ICommand* Command = new CreateUnitCommand(field, player);
        Command->Command();
    }
    else Chain::chain(command, player);

}
