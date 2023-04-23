#ifndef OOP1_LANDSCAPE_H
#define OOP1_LANDSCAPE_H

#include <string>
#include "LandscapeProtected.h"
#include "Unit.h"

class Landscape{
public:
    LandscapeProtected landscape;
    virtual bool isMoved(Unit* unit) = 0;
    virtual std::string getNameLandscape() = 0;
};

#endif //OOP1_LANDSCAPE_H
