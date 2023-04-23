//
// Created by Artem Butko on 28.05.2020.
//

#include "StateUndead.h"

void StateUndead::playerCommand(std::string command, Chain *player)
{
    player->chain(command, "U");
}
