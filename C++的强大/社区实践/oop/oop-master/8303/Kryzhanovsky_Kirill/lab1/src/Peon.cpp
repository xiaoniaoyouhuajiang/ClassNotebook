//
// Created by therealyou on 11.02.2020.
//

#include "Peon.h"

Peon::Peon() : Alliance(DEFAULT_SPEED, DEFAULT_ARMOR, DEFAULT_DAMAGE, DEFAULT_HEALTH){};

char Peon::getId() {
    return 'P';
}



