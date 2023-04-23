#ifndef RIDER_H
#define RIDER_H

#include "cavelry.h"
class Rider : public Cavelry{
public:
    Rider();
    string getName();
    Unit* copyItem();
    UnitsType getTypeEnum() const;
};

#endif // RIDER_H
