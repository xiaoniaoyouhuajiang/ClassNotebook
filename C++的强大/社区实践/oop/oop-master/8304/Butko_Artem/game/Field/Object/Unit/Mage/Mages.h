



#ifndef NEW_LR1_MAGES_H
#define NEW_LR1_MAGES_H


#include "../Unit.h"

class Mages : public Unit
{
public:
    Mages() = default;
    ~Mages() = default;

    Mages(int health, int damage, int range, int armor, char id);
    void regeneration(int heal) override;
    void selfDamage(int damage) override;
};


#endif //NEW_LR1_MAGES_H
