//
// Created by Artem Butko on 30.05.2020.
//

#include "SkipLink.h"


void SkipLink::chain(std::string command, std::string player)
{
    if (command == "/skip")
    {
        ICommand* Command = new SkipCommand(field, player);
        Command->Command();
    }
    else Chain::chain(command, player);
}
