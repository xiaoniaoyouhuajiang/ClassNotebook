//
// Created by Artem Butko on 20/05/2020.
//

#include "BaseInfoLink.h"

void BaseInfoLink::chain(std::string command)
{
    if (command == "/info_base")
    {
        ICommand* Command = new BaseInfoCommand(field);
        Command->Command();
    }
    else Chain::chain(command);
}
