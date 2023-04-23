


#include "StateBright.h"

void StateBright::playerCommand(std::string command, Chain *player)
{
    player->chain(command, "B");
}