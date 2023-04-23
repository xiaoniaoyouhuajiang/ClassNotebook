#ifndef OOP_MARADEURSCAMP_H
#define OOP_MARADEURSCAMP_H

#include "Neutral.h"


class MaradeursCamp : public Neutral, public Location {
public:
    MaradeursCamp(int x, int y);
    ~MaradeursCamp() = default;
    int operator()(Unit* unit) final;
private:
    strategy_health strategy;
};


#endif //OOP_MARADEURSCAMP_H
