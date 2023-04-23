



#ifndef NEW_LR1_MAGE_H
#define NEW_LR1_MAGE_H


#include "../Mages.h"

class Mage : public Mages
{
public:
    Mage() : Mages(50, 50, 100, 0, 'M') {};
    ~Mage() = default;
};


#endif //NEW_LR1_MAGE_H
