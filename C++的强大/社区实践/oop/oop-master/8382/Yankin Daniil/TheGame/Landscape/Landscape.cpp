#include "Landscape.h"


Landscape::Landscape(Point point) : point(point) {}

Point Landscape::getPoint() {
    return point;
}

int16_t Landscape::getMovementCost() {
    return movementCost;
}
