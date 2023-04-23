



#ifndef NEW_LR1_CROSSBOWMAN_H
#define NEW_LR1_CROSSBOWMAN_H


#include "../Archery.h"

class Crossbowman : public Archery
{
public:
    Crossbowman() : Archery(200, 60, 3, 0, 'C') {};
    ~Crossbowman() = default;
};


#endif //NEW_LR1_CROSSBOWMAN_H
