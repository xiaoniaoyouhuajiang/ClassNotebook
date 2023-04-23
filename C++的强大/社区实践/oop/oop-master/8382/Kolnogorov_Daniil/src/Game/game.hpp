#pragma once

#include "../Logging/formatter.hpp"
#include "../Logging/logger_proxy.hpp"
#include "Commands/command_memento.hpp"
#include "Field/coordinates.hpp"
#include "Field/field_proxy.hpp"
#include "Player/player.hpp"
#include "Rules/game_rule.hpp"
#include "Tiles/base.hpp"
#include "Units/concrete_unit_factory.hpp"
#include "Units/units.hpp"

class Game {
public:
    LoggerProxy* logger;
    vector<CommandMemento> command_history;

    GameRule* rule;

    FieldProxy* field;
    vector<Player*> players;

    Player* current_player;
    unsigned current_player_id;
    unsigned total_players;
    unsigned seed;
    bool running;

    Game(GameRule* rule);
    ~Game();

    void set_running(bool value) { running = value; };
    bool is_running() { return running; };

    bool is_owned_by(unsigned id, UnitInterface* unit);

    vector<Coordinates> get_reachable(Coordinates coors);
    bool unit_can_move(UnitInterface* unit);

    void set_logger(Logger* logger_) { logger->set_logger(logger_); };
    void set_log_formatter(LogFormatter* formatter) {
        logger->set_formatter(formatter);
    };
};
