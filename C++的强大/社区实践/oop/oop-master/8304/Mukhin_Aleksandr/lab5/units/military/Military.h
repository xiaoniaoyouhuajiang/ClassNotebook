#ifndef LAB2_MILITARY_H
#define LAB2_MILITARY_H


#include "Unit.h"

class Military : public Unit {
public:
    Military() = default;
    Military(int def, int att, int intell) : Unit(def, att, intell) {}

    void greeting() const override;
};


#endif
