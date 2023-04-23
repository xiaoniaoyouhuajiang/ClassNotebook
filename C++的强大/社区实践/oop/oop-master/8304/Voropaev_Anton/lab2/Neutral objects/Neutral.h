#ifndef OOP_NEUTRAL_H
#define OOP_NEUTRAL_H

#include "Stretegy.h"
#include "../Unit.h"
class Neutral{
public:
    Neutral() = default;
    virtual int operator()(Unit* obj) = 0;
};



#endif //OOP_NEUTRAL_H
