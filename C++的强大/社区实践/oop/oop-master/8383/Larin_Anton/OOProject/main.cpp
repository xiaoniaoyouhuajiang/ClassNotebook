#include <iostream>

#include "Game.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Game::setGameRules({true,9,9,{0,0},{8,8},true});
    //Game::setGameRules({false,9,9,{0,8},{8,0},false});
    Game game = Game::getInstance();
    game.setConsoleLoger();
    //game.setFileLogger("Log.txt");
    game.demo();
    return 0;
}