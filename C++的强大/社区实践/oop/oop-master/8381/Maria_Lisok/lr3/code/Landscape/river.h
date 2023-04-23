#ifndef RIVER_H
#define RIVER_H
#include "landscape.h"
class River : public Landscape{
public:
    string getLandscapeType();
    bool canStand();
    LandscapeType getLandscapeTypeEnum();
};
#endif // RIVER_H
