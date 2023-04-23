#ifndef OOP_HEALINGFOUNTAIN_H
#define OOP_HEALINGFOUNTAIN_H

#include "Neutral.h"

class HealingFountain: public Neutral, public Location{
public:
    HealingFountain(int x, int y);
    ~HealingFountain() = default;
    int operator()(Unit* unit) final;
private:
     strategy_health strategy;
};

#endif //OOP_HEALINGFOUNTAIN_H

