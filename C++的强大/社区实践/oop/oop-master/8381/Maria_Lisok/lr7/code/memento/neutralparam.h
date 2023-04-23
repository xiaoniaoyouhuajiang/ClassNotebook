#ifndef NEUTRALPARAM_H
#define NEUTRALPARAM_H
#include "enums.h"
class NeutralParam{
public:
    NeutralParam(NeutralType type, unsigned x, unsigned y);
    NeutralType getType() const;
    unsigned getX() const;
    unsigned getY() const;
private:
    NeutralType type;
    unsigned x;
    unsigned y;
};
#endif // NEUTRALPARAM_H
