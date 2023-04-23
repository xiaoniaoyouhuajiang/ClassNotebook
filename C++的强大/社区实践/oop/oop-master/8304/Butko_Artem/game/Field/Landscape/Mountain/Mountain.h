



#ifndef NEW_LR1_MOUNTAIN_H
#define NEW_LR1_MOUNTAIN_H

#include "../LandscapeInterface.h"
#include "../../Object/Object.h"

class Mountain : public LandscapeInterface
{
public:
    Mountain() = default;
    void getEffect(Object* object_) override;
    char getID() override;

private:
    char id_ ='^';
};


#endif //NEW_LR1_MOUNTAIN_H
