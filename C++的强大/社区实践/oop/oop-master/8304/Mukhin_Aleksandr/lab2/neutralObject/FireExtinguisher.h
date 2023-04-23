#ifndef LAB2_FIREEXTINGUISHER_H
#define LAB2_FIREEXTINGUISHER_H


#include "NeutralObject.h"

class FireExtinguisher : public NeutralObject {
public:
    FireExtinguisher() : NeutralObject(10, 0, 0) {}
};


#endif