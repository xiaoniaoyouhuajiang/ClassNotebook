//
// Created by therealyou on 11.02.2020.
//

#include "Elf.h"

Elf::Elf() : Magicians(DEFAULT_SPEED, DEFAULT_ARMOR, DEFAULT_DAMAGE, DEFAULT_HEALTH){};

char Elf::getId() {
    return 'E';
}
