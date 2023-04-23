#include "neutralparam.h"
NeutralParam::NeutralParam(NeutralType type, unsigned x, unsigned y):type(type), x(x), y(y)
{}

NeutralType NeutralParam::getType() const
{
    return type;
}

unsigned NeutralParam::getX() const
{
    return x;
}

unsigned NeutralParam::getY() const
{
    return y;
}
