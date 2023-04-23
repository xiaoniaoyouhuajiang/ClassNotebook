//
// Created by Artem Butko on 20/05/2020.
//

#include "GetUnitLink.h"

void GetUnitLink::chain(std::string command)
{
    if (command == "/get_unit")
    {
        ICommand* Command = new GetUnitCommand(field);
        Command->Command();
    }
    else Chain::chain(command);
}
