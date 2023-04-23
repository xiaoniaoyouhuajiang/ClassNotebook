#pragma once

#include "../Player/player.hpp"
#include "../Units/units.hpp"
#include "neutral.hpp"

class NeutralContext {
protected:
    NeutralInterface* neutral_strategy;

public:
    NeutralContext() { neutral_strategy = nullptr; };

    void set_neutral(NeutralInterface* neutral) { neutral_strategy = neutral; };

    void apply_to_unit(UnitInterface* unit) {
        if (neutral_strategy)
            neutral_strategy->apply_to_unit(unit);
    }

    void apply_to_player(Player* player) {
        if (neutral_strategy)
            neutral_strategy->apply_to_player(player);
    };
};
