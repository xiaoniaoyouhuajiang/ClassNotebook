//
// Created by Artem Butko on 27.05.2020.
//

#include "StateDark.h"

void StateDark::playerCommand(std::string command, Chain *player)
{
    player->chain(command, "D");
}
