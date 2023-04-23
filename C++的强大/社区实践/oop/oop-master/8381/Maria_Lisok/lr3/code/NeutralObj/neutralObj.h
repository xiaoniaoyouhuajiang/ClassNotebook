#ifndef NEUTRALOBJ_H
#define NEUTRALOBJ_H

#include "unit.h"

class NeutralObj{
public:
    virtual ~NeutralObj()=default;
    virtual void operator+=(Unit& unit)=0;
    virtual string characteristic()=0;
    virtual NeutralType getTypeEnum()=0;
};
#endif // NEUTRALOBJ_H
