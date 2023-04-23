//
// Created by Artem Butko on 21.05.2020.
//

#include "LoggingLink.h"

void LoggingLink::chain(std::string command, std::string player)
{
    if (command == "/logging")
    {
        ICommand* Command = new LoggingCommand(field);
        Command->Command();
    }
    else Chain::chain(command, player);
}
