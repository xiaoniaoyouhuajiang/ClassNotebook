#ifndef MOUNTAIN_H
#define MOUNTAIN_H
#include "landscape.h"
class Mountain: public Landscape{
public:
    string getLandscapeType();
    bool canStand();
    LandscapeType getLandscapeTypeEnum();
};
#endif // MOUNTAIN_H
