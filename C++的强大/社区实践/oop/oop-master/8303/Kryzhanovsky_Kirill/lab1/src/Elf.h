//
// Created by therealyou on 11.02.2020.
//

#ifndef LAB1_ELF_H
#define LAB1_ELF_H


#include "Magicians.h"

class Elf : public Magicians {

    const static int DEFAULT_SPEED = 3;
    const static int DEFAULT_HEALTH = 180;
    const static int DEFAULT_ARMOR = 5;
    const static int DEFAULT_DAMAGE = 18;

    char getId() override;

public:
    Elf();
};


#endif //LAB1_ELF_H
