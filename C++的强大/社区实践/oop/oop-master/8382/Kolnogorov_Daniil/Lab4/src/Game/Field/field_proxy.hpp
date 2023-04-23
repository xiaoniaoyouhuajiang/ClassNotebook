#pragma once

#include "field_interface.hpp"
#include "field_iterator.hpp"

class Field;

class FieldProxy : public FieldInterface {
protected:
    Field* field;

public:
    FieldProxy(unsigned width, unsigned height);
    ~FieldProxy();

    unsigned get_width();
    unsigned get_height();

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
    Coordinates random_empty();

    FieldIterator get_iterator();
};
