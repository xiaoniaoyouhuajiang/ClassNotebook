#ifndef ARCHER_H
#define ARCHER_H

#include "arrow.h"

class Archer: public Arrow{
public:
    Archer();
    string getName();
    Unit* copyItem();
    UnitsType getTypeEnum() const;
};

#endif // ARCHER_H
