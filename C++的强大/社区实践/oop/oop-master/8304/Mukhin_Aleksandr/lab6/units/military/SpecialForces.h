#ifndef LAB2_SPECIALFORCES_H
#define LAB2_SPECIALFORCES_H

#include "HealthPoints.h"
#include "Attack.h"
#include "Military.h"

class SpecialForces : public Military {
public:
    SpecialForces() : Military(11, 95, 30) {}
    void greeting() const override;
};


#endif
