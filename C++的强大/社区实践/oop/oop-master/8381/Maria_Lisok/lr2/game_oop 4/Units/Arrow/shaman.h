#ifndef SHAMAN_H
#define SHAMAN_H
#include "arrow.h"
class Shaman: public Arrow{
public:
    Shaman();
    string getName();
    Unit* copyItem();
};

#endif // SHAMAN_H
