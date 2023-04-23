//
// Created by max on 13.03.20.
//

#include "Bar.h"

void Bar::communication(Unit *unit) {
    unit->increaseMoral(2);
    unit->decreaseXp(1);
}
