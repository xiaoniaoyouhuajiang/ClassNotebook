#pragma once

#include "Field/Field.hpp"

class GameEndRule {
public:
    static bool gameOver(const std::shared_ptr<const Field>& field, int &winner) {
        bool players[2];
        for (const auto& [cell, position] : *field) {
            auto creature = cell->getCreature();
            if (creature != nullptr) {
                players[creature->getPlayer().value()] = true;
                winner = creature->getPlayer().value();
            }
        }
        if (players[0] && players[1])
            return false;
        return true;
    }
};