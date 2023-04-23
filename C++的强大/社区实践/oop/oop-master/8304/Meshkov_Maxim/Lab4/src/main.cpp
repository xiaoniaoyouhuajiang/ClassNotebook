#include <memory>

#include "Game.hpp"
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

    std::shared_ptr<GameInterface> game(new Game);

    if (logInFile)
        game.reset(new GameProxyWithFileLogging(game, "log.txt", logWithTime));
    if (logInConsole)
        game.reset(new GameProxyWithConsoleLogging(game, logWithTime));

    std::shared_ptr<Gui> gui(new Gui(game));
    gui->show();
    return 0;
}
