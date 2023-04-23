#ifndef ARROW_H
#define ARROW_H
#include "unit.h"
class Arrow: public Unit{
public:
    virtual Unit* copyItem() = 0;
};
#endif // ARROW_H
