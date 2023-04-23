#ifndef RIVER_H
#define RIVER_H
#include "landscape.h"
class River : public Landscape{
public:
    string getLandscapeType();
    bool canStand();
};
#endif // RIVER_H
