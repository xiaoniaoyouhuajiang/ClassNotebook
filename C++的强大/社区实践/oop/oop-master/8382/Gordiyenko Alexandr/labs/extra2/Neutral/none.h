#ifndef LABS_NONE_H
#define LABS_NONE_H

#include "neutralObject.h"

class NoneObj : public NeutralObject{
    void action(Unit *unit) {}
    char typeNeutral(){
        return ' ';
    }
};

#endif //LABS_NONE_H
