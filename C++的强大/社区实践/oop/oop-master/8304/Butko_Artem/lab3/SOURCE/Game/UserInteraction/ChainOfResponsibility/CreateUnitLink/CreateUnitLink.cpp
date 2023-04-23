//
// Created by Artem Butko on 20/05/2020.
//

#include "CreateUnitLink.h"

void CreateUnitLink::chain(std::string command)
{
    if (command == "/create_unit")
    {
        ICommand* Command = new CreateUnitCommand(field);
        Command->Command();
    }
    else Chain::chain(command);

}
