#include "Game/Rules/game_rule.hpp"
#include "Game/game.hpp"
#include "Game/game_facade.hpp"
#include "Logging/formatter_time.hpp"
#include "Logging/logger_file.hpp"
#include "Logging/logger_terminal.hpp"
#include "UI/render.hpp"
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(NULL));

    // GameFacadeInterface* game = GameFacade<GameRuleDeathmatch>::instance();
    GameFacadeInterface* game = GameFacade<GameRuleRegular>::instance();

    // game->set_logger(new LoggerFile("log.txt"));
    game->set_logger(new LoggerTerminal());

    game->set_log_formatter(new FormatterTime());

    Renderer renderer = Renderer(game);

    while (renderer.running()) {
        renderer.render();
    }

    renderer.close();

    return 0;
}
