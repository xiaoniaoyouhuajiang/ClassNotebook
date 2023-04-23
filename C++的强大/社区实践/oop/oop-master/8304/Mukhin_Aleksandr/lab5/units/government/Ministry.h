#ifndef LAB2_MINISTRY_H
#define LAB2_MINISTRY_H


#include "Government.h"

class Ministry : public Government {
public:
    Ministry() : Government(75, 60, 95) {}
    void greeting() const override;
};


#endif
