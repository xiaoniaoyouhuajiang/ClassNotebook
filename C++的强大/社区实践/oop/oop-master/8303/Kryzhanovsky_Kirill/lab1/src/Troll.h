//
// Created by therealyou on 11.02.2020.
//

#ifndef LAB1_TROLL_H
#define LAB1_TROLL_H


#include "Orcs.h"


class Troll : public Orcs {

    const static int DEFAULT_SPEED = 5;
    const static int DEFAULT_HEALTH = 220;
    const static int DEFAULT_ARMOR = 8;
    const static int DEFAULT_DAMAGE = 13;

    char getId() override;

public:
    Troll();
};


#endif //LAB1_TROLL_H
