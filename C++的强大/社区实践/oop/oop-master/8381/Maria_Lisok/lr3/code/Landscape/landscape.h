#ifndef LANDSCAPE_H
#define LANDSCAPE_H
#include "enums.h"
#include <iostream>
using namespace std;
class Landscape{
public:
    virtual ~Landscape()=default;
    virtual string getLandscapeType()=0;
    virtual LandscapeType getLandscapeTypeEnum()=0;
    virtual bool canStand()=0;
};
#endif
