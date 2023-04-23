#ifndef NEW_LR1_OBJECT_H
#define NEW_LR1_OBJECT_H

#include <cstdio>
#include "Attributes/Armor.h"
#include "Attributes/Damage.h"
#include "Attributes/Health.h"

class Object
{
public:
    Armor armor;
    Health health;
    Damage damage;
    size_t x_;
    size_t y_;
    char id_;
    bool isCanMove;
};


#endif //NEW_LR1_OBJECT_H
