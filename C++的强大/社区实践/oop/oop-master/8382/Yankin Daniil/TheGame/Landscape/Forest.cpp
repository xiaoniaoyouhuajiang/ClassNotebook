#include "Forest.h"


Forest::Forest(Point point) : Landscape(point) {
    movementCost = 2;
}

bool Forest::movementAccess() {
    return true;
}

uint16_t Forest::getObjectType() {
    return LAND_FOREST;
}
