#include "field.hpp"

#include "../Tiles/tiles.hpp"
#include "field_iterator.hpp"

using namespace std;

Field::Field(unsigned width, unsigned height)
    : width(max(40u, width)), height(max(40u, height)) {

    this->grid = new TileInterface**[height];
    for (unsigned y = 0; y < height; y++) {
        this->grid[y] = new TileInterface*[width];
    }

    generate_field();
}

Field::Field(const Field& other) : width(other.width), height(other.height) {
    grid = new TileInterface**[height];
    for (unsigned y = 0; y < height; y++) {
        grid[y] = new TileInterface*[width];
        for (unsigned x = 0; x < width; x++) {
            grid[y][x] = other.grid[y][x]->create_copy();
        }
    }
}

Field& Field::operator=(const Field& other) {
    if (this == &other) {
        return *this;
    }

    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {
            delete grid[y][x];
        }
        delete[] grid[y];
    }
    delete[] grid;

    grid = new TileInterface**[height];
    for (unsigned y = 0; y < height; y++) {
        grid[y] = new TileInterface*[width];
        for (unsigned x = 0; x < width; x++) {
            grid[y][x] = other.grid[y][x]->create_copy();
        }
    }

    return *this;
}

Field::Field(Field&& other)
    : width(other.width), height(other.height), grid(move(other.grid)) {
}

Field& Field::operator=(Field&& other) {
    if (this != &other) {
        grid = move(other.grid);
        width = other.width;
        height = other.height;
    }
    return *this;
}

Field::~Field() {
    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {
            delete grid[y][x];
        }
        delete[] grid[y];
    }
    delete[] grid;
}

void Field::generate_field() {
    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {
            Coordinates coors = {(int)x, (int)y};
            int r = rand() % 100;
            if (r < 15) {
                grid[y][x] = new Wall(coors);
            } else if (r < 30) {
                grid[y][x] = new Water(coors);
            } else {
                grid[y][x] = new Grass(coors);
            }
        }
    }
}

bool Field::fits_in_grid(unsigned x, unsigned y) {
    return (x < width && y < height);
}

bool Field::can_reach(Coordinates from, Coordinates to, int max_dist) {
    vector<Coordinates> reachable;
    if (max_dist == -1)
        reachable = get_reachable(from);
    else
        reachable = get_reachable(from, max_dist);

    for (auto v : reachable) {
        if (v == to) {
            return true;
        }
    }
    return false;
}

TileInterface* Field::tile_at(Coordinates coors) {
    if (coors.x < 0 || coors.y < 0 || !fits_in_grid(coors.x, coors.y)) {
        return NULL;
    }
    return grid[coors.y][coors.x];
}

void Field::place_unit_at(Coordinates coors, UnitInterface* unit) {
    TileInterface* tile = tile_at(coors);
    tile->set_unit(unit);
}

void Field::place_tile_at(Coordinates coors, TileInterface* tile) {
    if (tile_at(coors)) {
        delete tile_at(coors);
    }
    grid[coors.y][coors.x] = tile;
}

void Field::place_neutral_at(Coordinates coors, NeutralInterface* neutral) {
    TileInterface* tile = grid[coors.y][coors.x];
    tile->set_neutral(neutral);
}

UnitInterface* Field::unit_at(Coordinates coors) {
    TileInterface* tile = tile_at(coors);
    return tile->get_unit();
}

// NOTE: doesn't check if tile is walkable
vector<Coordinates> Field::get_reachable(Coordinates coors, int max_dist) {
    vector<Coordinates> reachable;

    if (max_dist <= 0)
        return reachable;

    for (int dx = -max_dist; dx <= max_dist; dx++) {
        for (int dy = -max_dist; dy <= max_dist; dy++) {
            int x = coors.x + dx;
            int y = coors.y + dy;
            if (fits_in_grid(x, y) &&
                (int)Coordinates::distance_manh({x, y}, coors) <= max_dist)
                reachable.push_back({x, y});
        }
    }

    return reachable;
}

void Field::move_unit(Coordinates from, Coordinates to) {
    TileInterface* tile_from = tile_at(from);
    TileInterface* tile_to = tile_at(to);
    UnitInterface* unit = tile_from->get_unit();

    tile_to->set_unit(unit);
    unit->set_moved(true);
    tile_from->set_unit(nullptr);
}

void Field::damage_tile(Coordinates coors, unsigned damage) {
    TileInterface* tile = tile_at(coors);
    UnitInterface* unit = tile->get_unit();

    bool target_is_base = (dynamic_cast<Base*>(tile) != nullptr);

    if (target_is_base) {
        Base* base = (Base*)tile;
        base->damage(damage);
    } else if (unit) {
        unit->damage(damage);
        if (unit->get_health() == 0) {
            unit->notify_about_death();
            tile->set_unit(nullptr);
            delete unit;
        }
    }
}

bool Field::unit_can_move_to(Coordinates) {
    return true;
}

bool Field::is_empty(Coordinates coors) {
    TileInterface* tile = tile_at(coors);
    return tile->get_can_walk() && !tile->get_unit() && !tile->get_neutral();
}

// NOTE: doesn't check if empty tile exists and can loop forever
Coordinates Field::random_empty() {
    while (true) {
        Coordinates coors = {(int)(rand() % width), (int)(rand() % height)};
        if (is_empty(coors)) {
            return coors;
        }
    }
}

FieldIterator Field::get_iterator() {
    return FieldIterator(this);
}
