#ifndef LAB2_ENGINEER_H
#define LAB2_ENGINEER_H


#include "Civilians.h"

class Engineer : public Civilians {
public:
    Engineer() : Civilians(50, 35, 95) {}
    void greeting() const override;
};


#endif
