#ifndef NEW_LR1_WARRIORS_H
#define NEW_LR1_WARRIORS_H


#include "../Unit.h"

class Warriors : public Unit
{
public:
    Warriors() = default;
    ~Warriors() = default;

    Warriors(int health, int damage, int range, int armor, char id);
    void regeneration(int heal) override;
    void selfDamage(int damage) override;
};


#endif //NEW_LR1_WARRIORS_H
