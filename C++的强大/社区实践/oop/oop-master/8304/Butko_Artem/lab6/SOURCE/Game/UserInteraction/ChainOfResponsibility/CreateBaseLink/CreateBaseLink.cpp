//
// Created by Artem Butko on 20/05/2020.
//

#include "CreateBaseLink.h"

void CreateBaseLink::chain(std::string command, std::string player)
{
    if (command == "/create_base")
    {
        ICommand* Command = new CreateBaseCommand(field);
        Command->Command();
    }
    else Chain::chain(command, player);
}
