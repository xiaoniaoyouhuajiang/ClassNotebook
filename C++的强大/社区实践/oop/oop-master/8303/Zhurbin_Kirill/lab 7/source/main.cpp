#include <iostream>
#include "Iterator.h"
#include "Game.h"

Game<Rule1, 2> *Game<Rule1, 2>::game = nullptr;
Game<Rule2, 2> *Game<Rule2, 2>::game = nullptr;
Game<Rule1, 3> *Game<Rule1, 3>::game = nullptr;
Game<Rule2, 3> *Game<Rule2, 3>::game = nullptr;

int main() {

    std::string modeGame;
    std::string countPlayers;

    std::cout << "Enter mode of game (battle or capture)" << std::endl;
    std::cin >> modeGame;
    while (modeGame != "battle" && modeGame != "capture"){
        std::cout << "Incorrect mode game, mode game can be battle or capture" << std::endl;
        std::cin >> modeGame;
    }

    std::cout << "Enter count of players" << std::endl;

    std::cin >> countPlayers;

    while (countPlayers != "2" && countPlayers != "3"){
        std::cout << "Incorrect count of players, count of players can be 2 or 3" << std::endl;
        std::cin >> countPlayers;
    }

    if (modeGame == "battle" && countPlayers == "2") {
        auto *game = Game<Rule1, 2>::getInstance();
        game->createGame();
        game->play();
    }
    else if (modeGame == "battle" && countPlayers == "3") {
        auto *game = Game<Rule1, 3>::getInstance();
        game->createGame();
        game->play();
    }
    else if (modeGame == "capture" && countPlayers == "2") {
        auto *game = Game<Rule2, 2>::getInstance();
        game->createGame();
        game->play();
    }
    else{
        auto* game = Game<Rule2, 3>::getInstance();
        game->createGame();
        game->play();
    }

    return 0;
}
