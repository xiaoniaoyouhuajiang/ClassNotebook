//

//

#ifndef NEW_LR1_FIELD_H
#define NEW_LR1_FIELD_H


#include "../LandscapeInterface.h"
#include "../../Object/Object.h"

class Field : public LandscapeInterface
{
public:
    Field() = default;
    void getEffect(Object* object_) override;
    char getID() override;

private:
    char id_ ='"';
};


#endif //NEW_LR1_FIELD_H
