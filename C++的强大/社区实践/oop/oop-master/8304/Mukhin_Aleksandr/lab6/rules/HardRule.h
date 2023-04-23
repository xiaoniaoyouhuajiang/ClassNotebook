#ifndef LAB2_HARDRULE_H
#define LAB2_HARDRULE_H

#include "Rule.h"

class HardRule : public Rule {
public:
    HardRule() : Rule(15, 15, 15, false, false, 3) {}
};


#endif