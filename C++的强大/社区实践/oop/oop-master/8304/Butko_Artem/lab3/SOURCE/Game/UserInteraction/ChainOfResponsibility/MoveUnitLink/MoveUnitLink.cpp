//
// Created by Artem Butko on 20/05/2020.
//

#include "MoveUnitLink.h"

void MoveUnitLink::chain(std::string command)
{
    if (command == "/move_unit")
    {
        ICommand* Command = new MoveUnitCommand(field);
        Command->Command();
    }
    else Chain::chain(command);
}
