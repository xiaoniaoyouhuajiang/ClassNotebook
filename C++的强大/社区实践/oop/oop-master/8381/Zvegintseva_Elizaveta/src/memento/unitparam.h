#ifndef UNITPARAM_H
#define UNITPARAM_H
#include "attributes.h"
#include <iostream>
using namespace std;
class UnitParam
{
public:
    UnitParam(string name, int baseNumber,  Attributes* attributes,  unsigned x,  unsigned y);
    string getName() const;

    int getBaseNumber() const;

    Attributes *getAttributes() const;

    unsigned getX() const;

    unsigned getY() const;

private:
    string name;
    int baseNumber;
    Attributes* attributes;
    unsigned x;
    unsigned y;
};

#endif // UNITPARAM_H
