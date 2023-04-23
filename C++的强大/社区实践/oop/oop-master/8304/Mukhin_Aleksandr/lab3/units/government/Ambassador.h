#ifndef LAB2_AMBASSADOR_H
#define LAB2_AMBASSADOR_H
#include "Government.h"

class Ambassador : public Government {
public:
    Ambassador() : Government(50, 55, 80) {}
    void greeting() const override;
};


#endif