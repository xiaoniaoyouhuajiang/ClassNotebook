#ifndef LAB2_CIVILIANS_H
#define LAB2_CIVILIANS_H


#include "Unit.h"

class Civilians : public Unit {
public:
    Civilians() = default;
    Civilians(int def, int att, int intell) : Unit(def, att, intell) {}
    void greeting() const override;
};


#endif
