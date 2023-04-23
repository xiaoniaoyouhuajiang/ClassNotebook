

#include "GameSaveLink.h"
#include "../../Commands/IRequest.h"
#include "../../Commands/SaveCommands/GameSaveRequest.h"

void GameSaveLink::chain(std::string command, std::string player)
{
    if (command == "/saveload")
    {
        IRequest* Command = new GameSaveRequest(field);
        Command->Command();
    }
    else Chain::chain(command, player);
}