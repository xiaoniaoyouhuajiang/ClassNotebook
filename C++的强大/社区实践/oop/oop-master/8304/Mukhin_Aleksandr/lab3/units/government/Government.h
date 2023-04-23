#ifndef LAB2_GOVERNMENT_H
#define LAB2_GOVERNMENT_H

#include "Unit.h"

class Government : public Unit {
public:
    Government() = default;
    Government(int def, int att, int intell) : Unit(def, att, intell) {}

    void greeting() const override;
};


#endif
