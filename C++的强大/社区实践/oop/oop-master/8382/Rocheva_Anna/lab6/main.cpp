#include <iostream>

#include "Game.hpp"

int main() {

    std::cout << "Rules:" << std::endl;
    std::cout << "1: Kill units\n2: Damage bases\nother: auto(Kill units)" << std::endl;
    int rule;
    std::cin >> rule;
    Rules *rules;
    switch (rule){
        case 1:{
            rules = new KillUnits;
            break;
        }
        case 2:{
            rules = new DamageBase;
            break;
        }
        default:
            rules = new KillUnits;
    }
    auto *game = new Game<Rules>(rules);
    game->startGame();

    return 0;
}
