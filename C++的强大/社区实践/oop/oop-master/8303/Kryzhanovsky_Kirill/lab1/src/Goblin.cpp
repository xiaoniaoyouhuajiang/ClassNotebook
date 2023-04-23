//
// Created by therealyou on 11.02.2020.
//

#include "Goblin.h"

Goblin::Goblin() : Orcs(DEFAULT_SPEED, DEFAULT_ARMOR, DEFAULT_DAMAGE, DEFAULT_HEALTH){};


char Goblin::getId() {
    return 'G';
}
