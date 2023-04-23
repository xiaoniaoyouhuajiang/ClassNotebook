#include "Rules/RuleOne/RuleOne.h"
#include "Rules/RuleTwo/RuleTwo.h"
#include "GameClass/GameClass.h"


void exec()
{
    int choice, players;
    std::cout << "------- GAME SETTINGS -------" << std::endl;
    std::cout << "Input type of rule (1 or 2) : ";
    std::cin >> choice;
    std::cout << "Input number of players (2 or 3) : ";
    if (choice == 1)
    {
        std::cin  >>  players;
        if (players == 2)
        {
            GameClass<RuleOne, 2> game;
            game.createGame();
            game.playGame();
        }
        else if (players == 3)
        {
            GameClass<RuleOne, 3> game;
            game.createGame();
            game.playGame();
        }
        else return;
    }
    else
    {
        std::cin  >>  players;
        if (players == 2)
        {
            GameClass<RuleTwo, 2> game;
            game.createGame();
            game.playGame();
        }
        else if (players == 3)
        {
            GameClass<RuleTwo, 3> game;
            game.createGame();
            game.playGame();
        }
        else return;
    }
    std::cout << "-----------------------------" << std::endl;

}

int main()
{
    exec();
    return 0;
}
