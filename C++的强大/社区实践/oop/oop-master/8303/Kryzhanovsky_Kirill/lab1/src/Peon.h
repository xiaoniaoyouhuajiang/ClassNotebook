//
// Created by therealyou on 11.02.2020.
//

#ifndef LAB1_PEON_H
#define LAB1_PEON_H

#include "Alliance.h"

class Peon : public Alliance {

    const static int DEFAULT_SPEED = 3;
    const static int DEFAULT_HEALTH = 210;
    const static int DEFAULT_ARMOR = 10;
    const static int DEFAULT_DAMAGE = 15;

    char getId() override;

public:
    Peon();
};


#endif //LAB1_PEON_H
