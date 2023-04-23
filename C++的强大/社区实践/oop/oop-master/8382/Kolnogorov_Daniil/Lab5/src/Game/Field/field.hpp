#pragma once

#include <utility>
#include <vector>

#include "../Neutral/neutral.hpp"
#include "../Tiles/base.hpp"
#include "../Tiles/tiles.hpp"
#include "../Units/units.hpp"
#include "coordinates.hpp"
#include "field_interface.hpp"
#include "field_iterator.hpp"

class Field : public FieldInterface {
protected:
    unsigned width;
    unsigned height;
    unsigned seed;
    TileInterface*** grid;

public:
    Field(unsigned width, unsigned height, unsigned seed);

    Field(const Field& other);
    Field& operator=(const Field& other);
    Field(Field&& other);
    Field& operator=(Field&& other);

    ~Field();

    unsigned get_width() { return width; };
    unsigned get_height() { return height; };
    unsigned get_seed() { return seed; };

    void generate_field();

    void move_unit(Coordinates from, Coordinates to);
    void damage_tile(Coordinates coors, unsigned damage);

    bool fits_in_grid(unsigned x, unsigned y);
    bool can_reach(Coordinates from, Coordinates to, int max_dist = -1);
    vector<Coordinates> get_reachable(Coordinates coors, int max_dist = -1);

    TileInterface* tile_at(Coordinates coors);
    void place_unit_at(Coordinates coors, UnitInterface* unit);
    void place_tile_at(Coordinates coors, TileInterface* tile);
    void place_neutral_at(Coordinates coors, NeutralInterface* neutral);

    UnitInterface* unit_at(Coordinates coors);

    bool unit_can_move_to(Coordinates coors);
    bool is_empty(Coordinates coors);
    Coordinates random_coors();

    FieldIterator get_iterator();
};
