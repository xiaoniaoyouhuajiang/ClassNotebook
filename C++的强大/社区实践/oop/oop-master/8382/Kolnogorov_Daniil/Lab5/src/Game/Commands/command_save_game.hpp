#pragma once

#include "commands.hpp"
#include "fstream"
#include <string>

using namespace std;

class CommandSaveGame : public Command {
public:
    CommandSaveGame(string filename) : filename(filename) {
        file.open(filename, ofstream::trunc);
    }

    ~CommandSaveGame() { file.close(); }

    void execute(Game* game) override {
        *game->logger << "[GAME] Saving game to " << filename << Logger::Endl();

        stringstream str_field;
        str_field << game->field->get_width() << " "
                  << game->field->get_height() << " " << game->field->get_seed()
                  << " " << game->total_players;

        hash<string> hash_function;
        unsigned long file_hash = hash_function(str_field.str());
        for (auto command : game->command_history) {
            file_hash += hash_function(command.memento);
        }

        file << file_hash << endl;
        file << str_field.str() << endl;
        for (auto command : game->command_history) {
            file << command.memento << endl;
        }

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
    ofstream file;
};

class SaveGameCommandHandler : public CommandHandler {
public:
    bool can_handle(vector<string> command) {
        return command.size() == 2 && command[0] == "save";
    }

    Command* handle(vector<string> command) {
        if (can_handle(command)) {
            return new CommandSaveGame(command[1]);
        } else if (next) {
            return next->handle(command);
        }
        return nullptr;
    };
};
