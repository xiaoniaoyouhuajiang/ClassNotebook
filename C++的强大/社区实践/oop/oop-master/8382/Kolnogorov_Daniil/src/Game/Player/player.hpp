#pragma once

#include "../../Logging/logger_proxy.hpp"
#include "../Tiles/base.hpp"
#include "../Units/units.hpp"

#define PLAYER_MAX_UNITS 5

class Player {
public:
    unsigned id;
    unsigned money;
    unsigned max_units;
    Base* base;
    vector<UnitInterface*> units;

    Player(unsigned id);
    ~Player();

    string get_info();
    Base* create_base(Coordinates coors);
    void set_base(Base* base);

    void add_unit(UnitInterface* unit);
    void react_unit_death(UnitInterface* unit);
    void react_base_death(TileInterface* base);

    friend LoggerProxy& operator<<(LoggerProxy& logger, const Player& player) {
        logger << to_string(player.id);
        return logger;
    }
};
