#ifndef LAB2_ABSTRACTIONBASE_H
#define LAB2_ABSTRACTIONBASE_H

#include "Unit.h"

class AbstractionBase {
public:
    virtual void add_unit(std::shared_ptr<Unit>&) = 0;
    virtual void get_base() = 0;
};


#endif
