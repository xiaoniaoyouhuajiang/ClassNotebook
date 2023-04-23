#ifndef NEW_LR1_TALE_H
#define NEW_LR1_TALE_H


#include "Object/Object.h"
#include "Object/Base.h"
#include "Landscape/LandscapeInterface.h"

class Tale
{
public:
    Tale() = default;
    ~Tale() = default;

    Tale(int x, int y);

    Object* object_;
    LandscapeInterface* landscape_;
    int x_;
    int y_;
};


#endif   //NEW_LR1_TALE_H
