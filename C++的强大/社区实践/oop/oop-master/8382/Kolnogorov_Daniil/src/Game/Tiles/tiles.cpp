#include "tiles.hpp"

using namespace std;

Tile::~Tile() {
    if (unit)
        delete unit;
    if (neutral)
        delete neutral;
}

bool Tile::can_place() {
    return can_walk && !unit;
}

Wall::Wall(Coordinates coors) {
    this->coors = coors;
    this->can_walk = false;
    this->can_build = false;
    this->type = TILE_WALL;
    this->unit = nullptr;
    this->neutral = nullptr;
}

TileInterface* Wall::create_copy() {
    TileInterface* copy = new Wall(coors);
    if (unit)
        copy->set_unit(unit->create_copy());
    if (neutral)
        copy->set_neutral(neutral->create_copy());
    return copy;
}

string Wall::get_info() {
    string info;
    info += "WALL";
    return info;
}

Grass::Grass(Coordinates coors) {
    this->coors = coors;
    this->can_walk = true;
    this->can_build = false;
    this->type = TILE_GRASS;
    this->unit = nullptr;
    this->neutral = nullptr;
}

TileInterface* Grass::create_copy() {
    TileInterface* copy = new Grass(coors);
    if (unit)
        copy->set_unit(unit->create_copy());
    if (neutral)
        copy->set_neutral(neutral->create_copy());
    return copy;
}

string Grass::get_info() {
    string info;
    info += "GRASS";
    return info;
}

Water::Water(Coordinates coors) {
    this->coors = coors;
    this->can_walk = false;
    this->can_build = false;
    this->type = TILE_WATER;
    this->unit = nullptr;
    this->neutral = nullptr;
}

TileInterface* Water::create_copy() {
    TileInterface* copy = new Water(coors);
    if (unit)
        copy->set_unit(unit->create_copy());
    if (neutral)
        copy->set_neutral(neutral->create_copy());
    return copy;
}

string Water::get_info() {
    string info;
    info += "WATER";
    return info;
}
