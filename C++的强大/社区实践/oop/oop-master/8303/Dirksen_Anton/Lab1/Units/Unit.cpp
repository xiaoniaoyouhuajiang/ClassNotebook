//
// Created by mensch on 02.03.2020.
//

#include <cassert>
#include "Unit.h"

void Unit::move(Point point) {
    assert(point.x >= 0);
    assert(point.y >= 0);
    coords = point;
}

ObjectType Unit::type() const{
    return UNIT;
}