//
// Created by Artem Butko on 22.05.2020.
//

#include "GameSaveLink.h"

void GameSaveLink::chain(std::string command)
{
    if (command == "/game")
    {
        ICommand* Command = new GameSaveCommand(field);
        Command->Command();
    }
    else Chain::chain(command);
}
