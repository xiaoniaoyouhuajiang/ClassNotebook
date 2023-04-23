#pragma once

#include "../Neutral/neutral.hpp"
#include "../Tiles/base.hpp"
#include "../Tiles/tiles.hpp"
#include "../Units/units.hpp"
#include "coordinates.hpp"
#include <utility>
#include <vector>

class FieldIterator;

class FieldInterface {
public:
    virtual ~FieldInterface() = default;
    virtual unsigned get_width() = 0;
    virtual unsigned get_height() = 0;

    virtual void generate_field() = 0;

    virtual void move_unit(Coordinates from, Coordinates to) = 0;
    virtual void damage_tile(Coordinates coors, unsigned damage) = 0;

    virtual bool fits_in_grid(unsigned x, unsigned y) = 0;
    virtual bool can_reach(Coordinates from, Coordinates to,
                           int max_dist = -1) = 0;
    virtual vector<Coordinates> get_reachable(Coordinates coors,
                                              int max_dist = -1) = 0;

    virtual TileInterface* tile_at(Coordinates coors) = 0;
    virtual void place_unit_at(Coordinates coors, UnitInterface* unit) = 0;
    virtual void place_tile_at(Coordinates coors, TileInterface* tile) = 0;
    virtual void place_neutral_at(Coordinates coors,
                                  NeutralInterface* neutral) = 0;

    virtual UnitInterface* unit_at(Coordinates coors) = 0;

    virtual bool unit_can_move_to(Coordinates coors) = 0;
    virtual bool is_empty(Coordinates coors) = 0;
    virtual Coordinates random_empty() = 0;

    virtual FieldIterator get_iterator() = 0;
};
