//
// Created by therealyou on 11.02.2020.
//

#include "Witch.h"

Witch::Witch() : Magicians(DEFAULT_SPEED, DEFAULT_ARMOR, DEFAULT_DAMAGE, DEFAULT_HEALTH){};


char Witch::getId() {
    return 'W';
}
