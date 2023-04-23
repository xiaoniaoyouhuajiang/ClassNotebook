
#include "StateDark.h"


void StateDark::playerCommand(std::string command, Chain *player)
{
    player->chain(command, "D");
}