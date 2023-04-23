#ifndef RIVERS_H
#define RIVERS_H
#include "landscape.h"

class River : public Landscape
{
public:

    River(){}
    bool canStand(std::string unit) override
    {
        return realLandscape.canStand();
    }
    bool canStand(Unit* unit) override
    {
        return realLandscape.canStand();
    }
    std::string getLandscapeType() override
    {
        return "River";
    }
};

#endif // RIVERS_H
