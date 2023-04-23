#ifndef NEW_LR1_UNIT_H
#define NEW_LR1_UNIT_H

#include <memory>
#include "../Object.h"

class Unit : public Object
{
public:
    Unit() = default;
    ~Unit() = default;
    virtual void regeneration(int heal) = 0;
    virtual void selfDamage(int damage) = 0;
};

#endif //NEW_LR1_UNIT_H
