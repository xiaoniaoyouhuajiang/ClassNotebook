#ifndef LAB2_DOCTOR_H
#define LAB2_DOCTOR_H

#include "Civilians.h"

class Doctor : public Civilians {
public:
    Doctor() : Civilians(65, 35, 95) {}
    void greeting() const override;
};


#endif
