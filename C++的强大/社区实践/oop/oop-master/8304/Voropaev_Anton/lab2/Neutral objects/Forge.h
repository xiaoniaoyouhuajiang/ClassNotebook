#ifndef OOP_FORGE_H
#define OOP_FORGE_H

#include "Neutral.h"

class Forge : public Neutral, public Location {
public:
    Forge(int x, int y);
    ~Forge() = default;
    int operator()(Unit* unit) final;
private:
    strategy_armor strategy;
};


#endif //OOP_FORGE_H
