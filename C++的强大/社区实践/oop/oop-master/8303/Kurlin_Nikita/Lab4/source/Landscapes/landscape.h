#ifndef LANDSCAPE_H
#define LANDSCAPE_H
#include <Landscapes/landscapeprotected.h>
#include "Units/unit.h"

//Proxy class for LandscapeProtected
class Landscape
{
public:
    LandscapeProtected realLandscape;

    virtual ~Landscape(){}
    virtual bool canStand(std::string unit) = 0;
    virtual bool canStand(Unit*) = 0;
    virtual std::string getLandscapeType() = 0;
};

#endif // LANDSCAPE_H
