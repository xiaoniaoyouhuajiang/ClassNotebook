//
// Created by therealyou on 11.02.2020.
//

#ifndef LAB1_GOBLIN_H
#define LAB1_GOBLIN_H


#include "Orcs.h"

class Goblin : public Orcs {

    const static int DEFAULT_SPEED = 4;
    const static int DEFAULT_HEALTH = 190;
    const static int DEFAULT_ARMOR = 12;
    const static int DEFAULT_DAMAGE = 16;

    char getId() override;

public:
    Goblin();

};


#endif //LAB1_GOBLIN_H
