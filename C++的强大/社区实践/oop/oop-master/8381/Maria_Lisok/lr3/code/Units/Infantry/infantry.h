#ifndef INFANTRY_H
#define INFANTRY_H
#include "unit.h"
class Infantry: public Unit{
public:
    virtual Unit* copyItem() = 0;
};
#endif // INFANTRY_H
