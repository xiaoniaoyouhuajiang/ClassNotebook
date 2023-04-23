//
// Created by Artem Butko on 22.05.2020.
//

#include "GameSaveLink.h"

void GameSaveLink::chain(std::string command, std::string player)
{
    if (command == "/saveload")
    {
        ICommand* Command = new GameSaveCommand(field);
        Command->Command();
    }
    else Chain::chain(command, player);
}
