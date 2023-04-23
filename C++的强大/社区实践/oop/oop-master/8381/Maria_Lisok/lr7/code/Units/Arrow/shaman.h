#ifndef SHAMAN_H
#define SHAMAN_H
#include "arrow.h"
class Shaman: public Arrow{
public:
    Shaman();
    string getName();
    Unit* copyItem();
    UnitsType getTypeEnum() const;
};

#endif // SHAMAN_H
