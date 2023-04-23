#pragma once

#include "../Units/units.hpp"
class Player;

class NeutralInterface {
public:
    virtual ~NeutralInterface() = default;
    virtual NeutralInterface* create_copy() = 0;
    virtual string get_info() = 0;
    virtual void apply_to_unit(UnitInterface* unit) = 0;
    virtual void apply_to_player(Player* player) = 0;
};
