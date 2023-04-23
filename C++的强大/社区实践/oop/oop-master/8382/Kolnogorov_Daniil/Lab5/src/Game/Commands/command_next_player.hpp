#pragma once

#include "commands.hpp"
#include "command_memento.hpp"

class CommandNextPlayer : public Command {
public:
    CommandNextPlayer() {}
    void execute(Game* game) override {
        game->rule->next_player(game);
        *game->logger << "[GAME] Passing turn to player "
                      << *game->current_player << Logger::Endl();
    }
    CommandMemento get_memento() override { return CommandMemento("next"); };
};

class NextPlayerCommandHandler : public CommandHandler {
public:
    bool can_handle(vector<string> command) {
        return command.size() == 1 && command[0] == "next";
    }

    Command* handle(vector<string> command) {
        if (can_handle(command)) {
            return new CommandNextPlayer();
        } else if (next) {
            return next->handle(command);
        }
        return nullptr;
    };
};
