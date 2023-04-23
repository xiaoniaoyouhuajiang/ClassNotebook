#include "GameSaveRequest.h"

void GameSaveRequest::Command()
{
    std::cout << "------- GAME SAVE ------" << std::endl;
    std::cout << "/save" << std::endl;
    std::cout << "/load" << std::endl;
    std::cout << "------------------------" << std::endl;
    std::string input;
    std::cout << "<command> : " ;
    std::cin >> input;
    if (input == "/save")
    {
        Snapshot* snapshot = field->createSnapshot("save");
        snapshot->saveGame();
    }
    else if (input == "/load")
    {
        Snapshot* snapshot = field->createSnapshot("load");
        field = snapshot->loadGame();
    }
    else
    {
        std::cout << "ERROR: wrong command of save" << std::endl;
    }
}