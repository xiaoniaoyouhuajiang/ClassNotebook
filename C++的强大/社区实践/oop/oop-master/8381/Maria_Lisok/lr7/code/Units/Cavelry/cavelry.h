#ifndef CAVELRY_H
#define CAVELRY_H
#include "unit.h"
class Cavelry: public Unit{
public:
    virtual Unit* copyItem() = 0;
};
#endif // CAVELRY_H
