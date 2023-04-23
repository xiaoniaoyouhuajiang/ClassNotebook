#pragma once

#include "command_create_unit.hpp"
#include "command_new_game.hpp"
#include "commands.hpp"
#include "interpreter.hpp"
#include <deque>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class CommandLoadGame : public Command {
public:
    CommandLoadGame(string filename) : filename(filename) {
        file.open(filename);
    }

    ~CommandLoadGame() { file.close(); }

    void execute(Game* game) override {
        if (!file.good()) {
            *game->logger << "[GAME] Error opening file " << filename
                          << Logger::Endl();
            return;
        }
        *game->logger << "[GAME] Loading game from " << filename
                      << Logger::Endl();

        hash<string> hash_function;
        string line;
        deque<string> lines;

        getline(file, line);
        unsigned long file_hash = stoul(line);
        unsigned long computed_hash = 0;

        while (getline(file, line)) {
            computed_hash += hash_function(line);
            lines.push_back(line);
        }

        if (computed_hash != file_hash) {
            *game->logger << "[GAME] Inavlid save file" << Logger::Endl();
            return;
        }

        getline(file, line);
        line = lines.front();
        lines.pop_front();

        stringstream ss(line);
        unsigned width;
        unsigned height;
        unsigned players;
        unsigned seed;
        ss >> width >> height >> seed >> players;
        computed_hash += hash_function(line);

        game->logger->disable_logging();

        CommandNewGame(width, height, players, seed).execute(game);
        Interpreter interpreter;
        for (auto cmd : lines) {
            Command* command = interpreter.handle(cmd);
            if (command) {
                command->execute(game);
                if (command->save_to_history()) {
                    game->command_history.push_back(command->get_memento());
                }
            }
        }

        game->logger->enable_logging();

        file.close();
    }

    CommandMemento get_memento() override {
        stringstream str;
        str << "save " << filename;
        return CommandMemento(str.str());
    }

    bool save_to_history() override { return false; }

private:
    string filename;
    ifstream file;
};

class LoadGameCommandHandler : public CommandHandler {
public:
    bool can_handle(vector<string> command) {
        return command.size() == 2 && command[0] == "save";
    }

    Command* handle(vector<string> command) {
        if (can_handle(command)) {
            return new CommandLoadGame(command[1]);
        } else if (next) {
            return next->handle(command);
        }
        return nullptr;
    };
};
