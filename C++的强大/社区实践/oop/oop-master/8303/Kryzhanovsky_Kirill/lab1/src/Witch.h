//
// Created by therealyou on 11.02.2020.
//

#ifndef LAB1_WITCH_H
#define LAB1_WITCH_H


#include "Magicians.h"

class Witch : public Magicians{

    const static int DEFAULT_SPEED = 4;
    const static int DEFAULT_HEALTH = 150;
    const static int DEFAULT_ARMOR = 3;
    const static int DEFAULT_DAMAGE = 25;

    char getId() override;

public:
    Witch();

};

#endif //LAB1_WITCH_H
