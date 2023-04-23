#include <iostream>
#include "GameFacade.h"
#include "Logs/Formats/TimeFormat.h"
#include "Logs/Loggers/FileLogger.h"
int main() {

    game::log.setLogger(new FileLogger("logs.txt"));
    game::log.setLogFormat(new TimeFormat());

    GameFacade game(2, 3, 3);

    while (!game.isOver()){

        std::cout << game;
        game.nextTurn();

    }

    return 0;
}