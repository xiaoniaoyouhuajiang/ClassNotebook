//
// Created by Artem Butko on 20/05/2020.
//

#include "UnknownLink.h"

void UnknownLink::chain(std::string command)
{
    ICommand* Command = new UnknownCommand();
    Command->Command();
}
