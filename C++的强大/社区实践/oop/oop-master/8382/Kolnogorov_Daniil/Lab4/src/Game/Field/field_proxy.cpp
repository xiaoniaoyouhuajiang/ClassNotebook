#include "field_proxy.hpp"
#include "field.hpp"

FieldProxy::FieldProxy(unsigned width, unsigned height) {
    field = new Field(width, height);
}

FieldProxy::~FieldProxy() {
    delete field;
}

unsigned FieldProxy::get_width() {
    return field->get_width();
}

unsigned FieldProxy::get_height() {
    return field->get_height();
}

void FieldProxy::generate_field() {
    field->generate_field();
}

void FieldProxy::move_unit(Coordinates from, Coordinates to) {
    TileInterface* tile_from = tile_at(from);
    TileInterface* tile_to = tile_at(to);
    UnitInterface* unit = tile_from->get_unit();

    if (!tile_to->get_can_walk() ||
        Coordinates::distance_manh(from, to) > unit->get_dexterity()) {
        return;
    }

    field->move_unit(from, to);
}

void FieldProxy::damage_tile(Coordinates coors, unsigned damage) {
    field->damage_tile(coors, damage);
}

bool FieldProxy::fits_in_grid(unsigned x, unsigned y) {
    return field->fits_in_grid(x, y);
}

bool FieldProxy::can_reach(Coordinates from, Coordinates to, int max_dist) {
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

vector<Coordinates> FieldProxy::get_reachable(Coordinates coors, int max_dist) {
    TileInterface* tile = tile_at(coors);
    vector<Coordinates> reachable;

    UnitInterface* unit = tile->get_unit();
    if (tile->get_type() != TILE_BASE && !unit) {
        return reachable;
    }

    if (max_dist == -1) {
        if (tile->get_type() == TILE_BASE) {
            max_dist = tile->get_max_dist();
        } else {
            max_dist = unit->get_dexterity();
        }
    }

    unsigned size = max(2 * max_dist + 1, 1);
    vector<vector<bool>> visited(size, vector<bool>(size, false));

    vector<pair<int, int>> dirs = {make_pair(-1, 0), make_pair(1, 0),
                                   make_pair(0, -1), make_pair(0, 1)};

    vector<pair<int, int>> to_visit = {make_pair(coors.x, coors.y)};

    for (int d = 0; d < max_dist; d++) {
        vector<pair<int, int>> to_visit_next;
        for (auto [cx, cy] : to_visit) {
            for (auto [dx, dy] : dirs) {
                int x = cx + dx;
                int y = cy + dy;

                int relx = max_dist + ((int)coors.x - x);
                int rely = max_dist + ((int)coors.y - y);

                if (!fits_in_grid(x, y) || visited[rely][relx]) {
                    continue;
                }

                visited[rely][relx] = true;

                TileInterface* tile = tile_at({x, y});
                if (!tile->get_can_walk() || tile->get_unit()) {
                    continue;
                }

                to_visit_next.push_back(make_pair(x, y));
                reachable.push_back({x, y});
            }
        }
        to_visit = to_visit_next;
    }

    return reachable;
}

TileInterface* FieldProxy::tile_at(Coordinates coors) {
    return field->tile_at(coors);
}

void FieldProxy::place_unit_at(Coordinates coors, UnitInterface* unit) {
    field->place_unit_at(coors, unit);
}

void FieldProxy::place_tile_at(Coordinates coors, TileInterface* tile) {
    field->place_tile_at(coors, tile);
}

void FieldProxy::place_neutral_at(Coordinates coors,
                                  NeutralInterface* neutral) {
    field->place_neutral_at(coors, neutral);
}

UnitInterface* FieldProxy::unit_at(Coordinates coors) {
    return field->unit_at(coors);
}

bool FieldProxy::unit_can_move_to(Coordinates coors) {
    TileInterface* tile = tile_at(coors);
    return tile->get_can_walk() && !tile->get_unit();
}

bool FieldProxy::is_empty(Coordinates coors) {
    TileInterface* tile = tile_at(coors);
    return tile->get_can_walk() && !tile->get_unit() && !tile->get_neutral();
}

Coordinates FieldProxy::random_empty() {
    return field->random_empty();
}

FieldIterator FieldProxy::get_iterator() {
    return field->get_iterator();
}
