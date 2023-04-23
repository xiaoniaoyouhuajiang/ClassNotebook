//
// Created by Artem Butko on 27.05.2020.
//

#include "StateBright.h"

void StateBright::playerCommand(std::string command, Chain *player)
{
    player->chain(command, "B");
}
