#ifndef OOP_TRAININGCAMP_H
#define OOP_TRAININGCAMP_H

#include "Neutral.h"

class TrainingCamp : public Neutral, public Location{
public:
    TrainingCamp() = default;
    TrainingCamp(int x, int y);
    ~TrainingCamp() = default;
    int operator()(Unit* unit) final;
private:
    strategy_dmg strategy;
    Neutral* t_camp = nullptr;
};

#endif //OOP_TRAININGCAMP_H
