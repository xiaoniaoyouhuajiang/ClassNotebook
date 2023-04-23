#include "unitparam.h"
UnitParam::UnitParam(string name, int baseNumber, Attributes *attributes, unsigned x, unsigned y):name(name), baseNumber(baseNumber), attributes(attributes),
   x(x), y(y)
{}
string UnitParam::getName() const
{
    return name;
}
int UnitParam::getBaseNumber() const
{
    return baseNumber;
}

Attributes *UnitParam::getAttributes() const
{
    return attributes;
}

unsigned UnitParam::getX() const
{
    return x;
}

unsigned UnitParam::getY() const
{
    return y;
}
