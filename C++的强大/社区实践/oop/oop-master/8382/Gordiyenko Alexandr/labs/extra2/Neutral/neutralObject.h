#ifndef LABS_NEUTRALOBJECT_H
#define LABS_NEUTRALOBJECT_H

#include "../../Units/Unit.h"

class NeutralObject{
public:
    char name;
    virtual void action(Unit *unit) = 0;

    virtual char typeNeutral() = 0;

    void operator>>(Unit* unit){
        action(unit);
    }
};

#endif //LABS_NEUTRALOBJECT_H
