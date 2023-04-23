//
// Created by therealyou on 11.02.2020.
//

#include "Shooter.h"

Shooter::Shooter() : Alliance(DEFAULT_SPEED, DEFAULT_ARMOR, DEFAULT_DAMAGE, DEFAULT_HEALTH){};

char Shooter::getId() {
    return 'S';
}
