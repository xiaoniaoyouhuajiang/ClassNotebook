//
// Created by Artem Butko on 20/05/2020.
//

#include "BaseInfoLink.h"

void BaseInfoLink::chain(std::string command, std::string player)
{
    if (command == "/info")
    {
        ICommand* Command = new BaseInfoCommand(field, player);
        Command->Command();
    }
    else Chain::chain(command, player);
}
