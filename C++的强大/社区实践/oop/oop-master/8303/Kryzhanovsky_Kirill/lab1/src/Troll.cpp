//
// Created by therealyou on 11.02.2020.
//

#include "Troll.h"

Troll::Troll() : Orcs(DEFAULT_SPEED, DEFAULT_ARMOR, DEFAULT_DAMAGE, DEFAULT_HEALTH){};


char Troll::getId() {
    return 'T';
}
