#include "Mountain.h"


Mountain::Mountain(Point point) : Landscape(point) {
    movementCost = 0;
}

bool Mountain::movementAccess() {
    return false;
}

uint16_t Mountain::getObjectType() {
    return LAND_MOUNTAIN;
}
