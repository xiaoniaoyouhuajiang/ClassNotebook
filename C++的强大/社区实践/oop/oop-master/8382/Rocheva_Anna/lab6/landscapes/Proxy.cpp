#include "Proxy.hpp"

Proxy::Proxy(Land land){
    switch (land){
        case GRASS:
            landscape = new Grass();
            break;
        case FOREST:
            landscape = new Forest();
            break;
        case MOUNTAINS:
            landscape = new Mountains();
            break;
        case SWAMP:
            landscape = new Swamp();
            break;
    }
}

void Proxy::changeAttribute(Unit *unit) {
    if (unit->getUnitName() == GUARDSMEN || unit->getUnitName() == CANNON || unit->getUnitName() == TANK)
        landscape->changeAttribute(unit);
}
