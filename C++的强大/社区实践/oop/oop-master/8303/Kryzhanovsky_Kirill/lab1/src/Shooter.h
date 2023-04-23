//
// Created by therealyou on 11.02.2020.
//

#ifndef LAB1_SHOOTER_H
#define LAB1_SHOOTER_H

#include "Alliance.h"

class Shooter : public Alliance {

    const static int DEFAULT_SPEED = 4;
    const static int DEFAULT_HEALTH = 280;
    const static int DEFAULT_ARMOR = 7;
    const static int DEFAULT_DAMAGE = 20;

    char getId() override;

public:
    Shooter();
};


#endif //LAB1_SHOOTER_H
