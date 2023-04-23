#include <iostream>
#include "GameFacade.h"
#include "Logs/Formats/TimeFormat.h"
#include "Logs/Loggers/FileLogger.h"
#include "Rules/SmallGame.h"
#include "Rules/BigGame.h"
#include "Logs/Loggers/TerminalLogger.h"

int main() {

    game::log.setLogger(new TerminalLogger());
    game::log.setLogFormat(new TimeFormat());

    auto game = GameFacade<SmallGame, 3>::instance();

    while (!game.isOver()){

        std::cout << game;
        game.nextTurn();

    }

    return 0;
}
