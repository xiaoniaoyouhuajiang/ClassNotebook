#include "Water.h"


Water::Water(Point point) : Landscape(point) {
    movementCost = 0;
}

bool Water::movementAccess() {
    return false;
}

uint16_t Water::getObjectType() {
    return LAND_WATER;
}
