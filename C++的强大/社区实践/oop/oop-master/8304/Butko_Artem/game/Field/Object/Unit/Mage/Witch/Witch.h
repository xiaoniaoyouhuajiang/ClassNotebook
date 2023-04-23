



#ifndef NEW_LR1_WITCH_H
#define NEW_LR1_WITCH_H

#include "../Mages.h"

class Witch :  public Mages
{
public:
    Witch() : Mages(20, 40, 20, 50, 'W') {};
    ~Witch() = default;
};


#endif //NEW_LR1_WITCH_H
