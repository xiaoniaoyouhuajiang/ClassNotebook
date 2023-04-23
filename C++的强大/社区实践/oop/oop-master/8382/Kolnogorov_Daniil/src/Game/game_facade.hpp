#pragma once

#include "Commands/commands.hpp"
#include "Commands/interpreter.hpp"
#include "Field/coordinates.hpp"
#include "Tiles/tiles.hpp"
#include "Units/units.hpp"
#include "game.hpp"
#include <vector>

class GameFacadeInterface {
public:
    virtual void execute(Command* command) = 0;
    virtual void execute(string command) = 0;
    virtual unsigned get_current_player_id() = 0;
    virtual Player* get_current_player() = 0;
    virtual unsigned get_width() = 0;
    virtual unsigned get_height() = 0;
    virtual unsigned get_players() = 0;
    virtual bool is_running() = 0;
    virtual TileInterface* tile_at(Coordinates coors) = 0;
    virtual vector<Coordinates> get_reachable(Coordinates from_coors) = 0;
    virtual bool unit_can_move(UnitInterface* unit) = 0;
    virtual bool is_owned_by(unsigned id, UnitInterface* unit) = 0;
    virtual string get_info() = 0;
    virtual void set_logger(Logger* logger_) = 0;
    virtual void set_log_formatter(LogFormatter* formatter) = 0;
};

template <typename Rule>
class GameFacade : public GameFacadeInterface {
public:
    static GameFacadeInterface* instance() {
        static GameFacade inst;
        return &inst;
    }

    void execute(Command* command) {
        if (command) {
            command->execute(game);
            if (command->save_to_history()) {
                game->command_history.push_back(command->get_memento());
            }
            delete command;
        }
    }

    void execute(string command) { execute(interpreter.handle(command)); }

    unsigned get_current_player_id() { return game->current_player_id; }
    Player* get_current_player() { return game->current_player; }
    unsigned get_width() { return game->field->get_width(); }
    unsigned get_height() { return game->field->get_height(); }
    unsigned get_players() { return game->total_players; }

    bool is_running() { return game->is_running(); }

    TileInterface* tile_at(Coordinates coors) {
        return game->field->tile_at(coors);
    }

    vector<Coordinates> get_reachable(Coordinates from_coors) {
        return game->field->get_reachable(from_coors);
    }

    bool unit_can_move(UnitInterface* unit) {
        return game->rule->unit_can_move(game, unit);
    }

    bool is_owned_by(unsigned id, UnitInterface* unit) {
        return id == unit->get_owner_id();
    }

    string get_info() {
        string text = game->rule->get_name() + "\n";
        if (game->rule->is_game_end(game)) {
            text += string("GAME ENDED\n");
        }
        text += game->current_player->get_info();
        return text;
    }

    void set_logger(Logger* logger_) { game->logger->set_logger(logger_); };
    void set_log_formatter(LogFormatter* formatter) {
        game->logger->set_formatter(formatter);
    };

private:
    Game* game;
    Interpreter interpreter;

    GameFacade() { game = new Game(new Rule()); }
};
