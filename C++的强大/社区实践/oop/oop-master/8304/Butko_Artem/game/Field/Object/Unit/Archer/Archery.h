



#ifndef NEW_LR1_ARCHERY_H
#define NEW_LR1_ARCHERY_H


#include "../Unit.h"

class Archery : public Unit
{
public:
    Archery() = default;
    ~Archery() = default;

    Archery(int health, int damage, int range, int armor, char id);
    void regeneration(int heal) override;
    void selfDamage(int damage) override;
};


#endif //NEW_LR1_ARCHERY_H
