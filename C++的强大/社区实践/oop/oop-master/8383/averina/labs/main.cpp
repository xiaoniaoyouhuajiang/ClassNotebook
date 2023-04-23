#include <iostream>
#include "Unit/Object/ObjectFactory.h"
#include "Field/Field.h"
#include "Battle/Rules/RuleFirst.h"
#include "Battle/GameClass.h"
#include "Battle/Rules/RuleSecond.h"



void start()
{
    int choice, players;
//    std::cout << "------- GAME SETTINGS -------" << std::endl;
    std::cout << "Nice to meet you! Welcome!\n";
    std::cout << "Let's play a game. The kingdoms have long been at odds with each other, "
                 "\nbut now the hatred is especially strong. Your mission will be to take "
                 "\ncommand of the troops and finally decide who is stronger!\n\n";
    std::cout << "There are two versions of the game: \n"
                 "\nFirst: the army will win if the enemy's base is destroyed. \n"
                 "Only 5 units can be created and stored on the base.\n";
    std::cout << "\nSecond: An army will lose if its base is destroyed or the number "
                 "\nof dead units on the field is 10. Only 3 units can be created and stored on the base.\n";

    std::cout << "Make your choice and may the force come with you, good luck...\n\n";
    std::cout << "Input type of rule (1 or 2) : ";
    std::cin >> choice;
    std::cout << "Input number of players (2 or 3) : ";
    if (choice == 1)
    {
        std::cin  >>  players;
        if (players == 2)
        {
            GameClass<RuleFirst, 2> game;
            game.createGame();
            game.playGame();
        }
        else if (players == 3)
        {
            GameClass<RuleFirst, 3> game;
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
            GameClass<RuleSecond, 2> game;
            game.createGame();
            game.playGame();
        }
        else if (players == 3)
        {
            GameClass<RuleSecond, 3> game;
            game.createGame();
            game.playGame();
        }
        else return;
    }
    std::cout << "-----------------------------" << std::endl;

}

int main(int argc, char * argv[])
{
    start();
    return 0;
}