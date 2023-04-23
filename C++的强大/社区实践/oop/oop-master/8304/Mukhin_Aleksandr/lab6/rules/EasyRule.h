#ifndef LAB2_EASYRULE_H
#define LAB2_EASYRULE_H

#include "Rule.h"

class EasyRule : public Rule {
public:
    EasyRule() : Rule(4, 4, 2, true, true, 2) {}
};


#endif
