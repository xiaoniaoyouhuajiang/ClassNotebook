#pragma once

#include <vector>

#include "../Units/units.hpp"
#include "tiles.hpp"

#define BASE_MAX_DISTANCE 3
#define BASE_HEALTH_MAX   200

class Player;

using namespace std;

class Base : public Tile {
public:
    unsigned owner_id;
    unsigned health_max;
    unsigned health;

    Base(Player* owner, Coordinates coors);
    TileInterface* create_copy();

    void damage(unsigned damage);
    void notify_about_death();

    string get_info();
private:
    Player* owner;
};
