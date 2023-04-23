#include <memory>

#include "Game.hpp"
#include "GameStartRule.hpp"
#include "GameEndRule.hpp"
#include "Logging/GameProxyWithFileLogging.hpp"
#include "Logging/GameProxyWithConsoleLogging.hpp"
#include "Gui/Gui.hpp"

#include <cstring>

int main(int argc, char* argv[]) {
    bool logWithTime = false;
    bool logInFile = false;
    bool logInConsole = false;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0)
            logInFile = true;
        if (strcmp(argv[i], "-c") == 0)
            logInConsole = true;
        if (strcmp(argv[i], "-t") == 0)
            logWithTime = true;
    }

    try {
        //    std::shared_ptr<GameInterface> game(new Game);
        std::shared_ptr<GameInterface> game = Game<GameStartRule, GameEndRule>::getInstance();

        if (logInFile)
            game.reset(new GameProxyWithFileLogging(game, "log.txt", logWithTime));
        if (logInConsole)
            game.reset(new GameProxyWithConsoleLogging(game, logWithTime));

        std::shared_ptr<Gui> gui(new Gui(game));
        gui->show();
    }
    catch (const std::exception &e) {
        std::cerr << "Critical error: " << e.what() << std::endl;
    }

    return 0;
}
