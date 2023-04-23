#pragma once

#include <string>

#include "../Field/coordinates.hpp"
#include "../Neutral/neutral.hpp"
#include "../Units/units.hpp"

using namespace std;

typedef enum {
    TILE_WALL,
    TILE_GRASS,
    TILE_WATER,
    TILE_BASE,
} tile_type;

class TileInterface {
public:
    virtual ~TileInterface() = default;

    virtual TileInterface* create_copy() = 0;

    virtual UnitInterface* get_unit() = 0;
    virtual void set_unit(UnitInterface* unit) = 0;
    virtual NeutralInterface* get_neutral() = 0;
    virtual void set_neutral(NeutralInterface* neutral) = 0;
    virtual Coordinates get_coors() = 0;
    virtual void set_coors(Coordinates coors) = 0;

    virtual tile_type get_type() = 0;
    virtual bool get_can_walk() = 0;
    virtual bool get_can_build() = 0;
    virtual unsigned get_max_dist() = 0;

    virtual bool can_place() = 0;
    virtual string get_info() = 0;
};

class Tile : public TileInterface {
protected:
    UnitInterface* unit;
    NeutralInterface* neutral;
    Coordinates coors;

    tile_type type;
    bool can_walk;
    bool can_build;
    unsigned max_dist; // TODO remove this workaround

public:
    virtual TileInterface* create_copy() = 0;
    ~Tile();

    tile_type get_type() { return type; };
    bool get_can_walk() { return can_walk; };
    bool get_can_build() { return can_build; };
    unsigned get_max_dist() { return max_dist; };

    UnitInterface* get_unit() { return unit; };
    void set_unit(UnitInterface* unit) { this->unit = unit; };
    NeutralInterface* get_neutral() { return neutral; };
    void set_neutral(NeutralInterface* neutral) { this->neutral = neutral; };
    Coordinates get_coors() { return coors; };
    void set_coors(Coordinates coors) { this->coors = coors; };

    bool can_place();

    virtual string get_info() = 0;
};

class Wall : public Tile {
public:
    Wall(Coordinates coors);
    TileInterface* create_copy();
    string get_info();
};

class Grass : public Tile {
public:
    Grass(Coordinates coors);
    TileInterface* create_copy();
    string get_info();
};

class Water : public Tile {
public:
    Water(Coordinates coors);
    TileInterface* create_copy();
    string get_info();
};
