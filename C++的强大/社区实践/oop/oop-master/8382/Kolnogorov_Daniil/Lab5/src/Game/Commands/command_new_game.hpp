#pragma once

#include "commands.hpp"
#include "sstream"
#include <string>

#include <cstdlib>

using namespace std;

class CommandNewGame : public Command {
public:
    CommandNewGame(unsigned width, unsigned height, unsigned players,
                   unsigned seed = rand())
        : width(width), height(height), seed(seed), players(players) {}

    void execute(Game* game) override {
        for (auto player : game->players) {
            delete player;
        }
        game->players.clear();
        game->current_player = nullptr;
        game->current_player_id = -1;
        game->total_players = players;
        // game->seed = seed;

        game->field = new FieldProxy(width, height, seed);

        game->rule->initialize_game(game, players);

        *game->logger << "[GAME] Starting new game with width " << width
                      << ", height " << height << " and " << players
                      << " players"
                      << " (seed is " << seed << ")" << Logger::Endl();

        game->set_running(true);
    }

    CommandMemento get_memento() override {
        stringstream str;
        str << "newgame " << width << " " << height << " " << players;
        return CommandMemento(str.str());
    }

    bool save_to_history() override { return false; }

private:
    unsigned width;
    unsigned height;
    unsigned seed;
    unsigned players;
};

class NewGameCommandHandler : public CommandHandler {
public:
    bool can_handle(vector<string> command) {
        return (command.size() == 4 || command.size() == 5) &&
               command[0] == "newgame";
    }

    Command* handle(vector<string> command) {
        if (can_handle(command)) {
            unsigned width = stoi(command[1]);
            unsigned height = stoi(command[2]);
            unsigned player = stoi(command[3]);
            unsigned seed = command.size() == 5 ? stoi(command[4]) : rand();
            return new CommandNewGame(width, height, seed, player);
        } else if (next) {
            return next->handle(command);
        }
        return nullptr;
    };
};
