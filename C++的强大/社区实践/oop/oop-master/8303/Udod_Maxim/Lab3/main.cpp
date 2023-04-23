#include <iostream>
#include "GameFacade.h"

int main() {

    auto unit = new FireMage;

    GameFacade game(2, 3, 3);

    while (!game.isOver()){

        std::cout << game;
        game.nextTurn();

    }

    return 0;
}
