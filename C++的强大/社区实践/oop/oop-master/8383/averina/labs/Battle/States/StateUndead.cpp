

#include "StateUndead.h"

void StateUndead::playerCommand(std::string command, Chain *player)
{
    player->chain(command, "U");
}