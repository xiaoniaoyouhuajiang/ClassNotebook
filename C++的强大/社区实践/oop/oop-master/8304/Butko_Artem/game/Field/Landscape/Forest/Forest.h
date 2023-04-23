//

//

#ifndef NEW_LR1_FOREST_H
#define NEW_LR1_FOREST_H

#include "../LandscapeInterface.h"
#include "../../Object/Object.h"

class Forest : public LandscapeInterface
{
public:
    Forest() = default;
    void getEffect(Object* object_) override;
    char getID() override;

private:
    char id_ ='?';
};


#endif //NEW_LR1_FOREST_H
