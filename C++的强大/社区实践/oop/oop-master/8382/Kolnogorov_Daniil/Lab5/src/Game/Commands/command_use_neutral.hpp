#pragma once

#include "../Neutral/neutral_context.hpp"
#include "../Units/units.hpp"
#include "command_memento.hpp"
#include "commands.hpp"
#include <sstream>

using namespace std;

class CommandUseNeutral : public Command {
public:
    CommandUseNeutral(Coordinates coors) : coors(coors) {}

    void execute(Game* game) override {
        UnitInterface* unit = game->field->unit_at(coors);
        TileInterface* tile = game->field->tile_at(coors);

        if (!unit) {
            return;
        }

        if (!game->is_owned_by(game->current_player_id, unit) ||
            !game->rule->unit_can_move(game, unit)) {
            return;
        }

        if (tile->get_neutral()) {
            *game->logger << "[GAME] Applying neutral object to unit at "
                          << coors << Logger::Endl();
            NeutralInterface* neutral = tile->get_neutral();
            NeutralContext neutral_cont;
            neutral_cont.set_neutral(neutral);
            neutral_cont.apply_to_unit(unit);
            neutral_cont.apply_to_player(game->current_player);
            tile->set_neutral(nullptr);
        }
    }

    CommandMemento get_memento() override {
        stringstream str;
        str << "use " << coors;
        return CommandMemento(str.str());
    }

private:
    Coordinates coors;
};

class UseNeutralCommandHandler : public CommandHandler {
public:
    bool can_handle(vector<string> command) {
        return command.size() == 2 && command[0] == "use";
    }

    Command* handle(vector<string> command) {
        if (can_handle(command)) {
            Coordinates coors(command[1]);
            return new CommandUseNeutral(coors);
        } else if (next) {
            return next->handle(command);
        }
        return nullptr;
    };
};
