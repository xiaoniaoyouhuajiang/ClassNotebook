#pragma once

#include "../Tiles/tiles.hpp"
#include "coordinates.hpp"

class Field;

class FieldIterator {
public:
    Field* field;
    Coordinates current;

    FieldIterator(Field* field);

    bool has_more();
    FieldIterator& operator++();
    TileInterface* operator*();
};
