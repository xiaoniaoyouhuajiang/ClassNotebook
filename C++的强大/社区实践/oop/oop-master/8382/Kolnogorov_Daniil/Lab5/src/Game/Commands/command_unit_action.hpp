#pragma once

#include "command_memento.hpp"
#include "commands.hpp"
#include <sstream>

class CommandUnitAction : public Command {
public:
    CommandUnitAction(Coordinates from_coors, Coordinates to_coors)
        : from_coors(from_coors), to_coors(to_coors) {}
    void execute(Game* game) override {
        TileInterface* tile_from = game->field->tile_at(from_coors);
        UnitInterface* unit = tile_from->get_unit();

        if (!unit)
            return;

        if (game->field->unit_can_move_to(to_coors)) {
            // game->move_unit(from_coors, to_coors);
            UnitInterface* unit = game->field->unit_at(from_coors);

            if (!game->is_owned_by(game->current_player_id, unit) ||
                !game->rule->unit_can_move(game, unit)) {
                return;
            }

            if (!game->field->can_reach(from_coors, to_coors)) {
                return;
            }

            *game->logger << "[Player] Moving unit from " << from_coors
                          << " to " << to_coors << Logger::Endl();

            game->field->move_unit(from_coors, to_coors);
        } else if (!unit->get_attacked() &&
                   Coordinates::distance_manh(from_coors, to_coors) <=
                       unit->get_range()) {
            *game->logger << "[Player] Unit at " << from_coors
                          << " damages tile at " << to_coors << " for "
                          << unit->get_strength() << " HP" << Logger::Endl();
            game->field->damage_tile(to_coors, unit->get_strength());
            unit->set_attacked(true);
        }
    }

    CommandMemento get_memento() override {
        stringstream str;
        str << "unit " << from_coors << " " << to_coors;
        return CommandMemento(str.str());
    };

private:
    Coordinates from_coors;
    Coordinates to_coors;
};

class UnitActionCommandHandler : public CommandHandler {
public:
    bool can_handle(vector<string> command) {
        return command.size() == 3 && command[0] == "unit";
    }

    Command* handle(vector<string> command) {
        if (can_handle(command)) {
            Coordinates from_coors(command[1]);
            Coordinates to_coors(command[2]);
            return new CommandUnitAction(from_coors, to_coors);
        } else if (next != nullptr) {
            return next->handle(command);
        }
        return nullptr;
    };
};
