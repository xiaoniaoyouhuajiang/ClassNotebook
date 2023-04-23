#ifndef LAB1_INFANTRY_H
#define LAB1_INFANTRY_H
#include "Unit.h"

class Infantry : public Unit {
public:
    char greeting() const override;
};

#endif
