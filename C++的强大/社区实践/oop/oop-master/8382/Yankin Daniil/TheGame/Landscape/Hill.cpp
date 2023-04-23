#include "Hill.h"


Hill::Hill(Point point) : Landscape(point) {
    movementCost = 2;
}

bool Hill::movementAccess() {
    return true;
}

uint16_t Hill::getObjectType() {
    return LAND_HILL;
}
