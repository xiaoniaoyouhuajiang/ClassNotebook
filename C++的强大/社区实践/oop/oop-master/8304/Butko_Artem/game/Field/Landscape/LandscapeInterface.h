//

//

#ifndef NEW_LR1_LANDSCAPEINTERFACE_H
#define NEW_LR1_LANDSCAPEINTERFACE_H

#include "../Object/Object.h"

class LandscapeInterface
{
public:
    virtual void getEffect(Object* object_) = 0;
    virtual char getID() = 0;
};


#endif //NEW_LR1_LANDSCAPEINTERFACE_H
