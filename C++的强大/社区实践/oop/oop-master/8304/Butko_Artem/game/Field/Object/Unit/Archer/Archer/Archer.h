



#ifndef NEW_LR1_ARCHER_H
#define NEW_LR1_ARCHER_H


#include "../Archery.h"

class Archer : public Archery
{
public:
    Archer() : Archery(150, 60, 3, 0, 'A') {};
    ~Archer() = default;
};


#endif //NEW_LR1_ARCHER_H
