#ifndef LAB2_AIRBORNE_H
#define LAB2_AIRBORNE_H


#include "Military.h"

class Airborne : public Military {
public:
    Airborne() : Military(80, 80, 40) {}
    void greeting() const override;
};


#endif
