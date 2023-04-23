#include "kill.h"
//#include "objects/units/unit.h"

void Kill::interact(Unit *unit) {
    unit->health = 0;
}

Kill::~Kill() {}
