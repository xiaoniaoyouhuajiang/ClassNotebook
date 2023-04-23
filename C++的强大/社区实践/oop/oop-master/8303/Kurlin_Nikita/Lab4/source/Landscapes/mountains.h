#ifndef MOUNTAINS_H
#define MOUNTAINS_H
#include "landscape.h"

class Mountain : public Landscape
{
public:

    Mountain(){}
    bool canStand(std::string unit) override
    {
        return realLandscape.cantStand();
    }
    bool canStand(Unit* unit) override
    {
        return realLandscape.cantStand();
    }
    std::string getLandscapeType() override
    {
        return "Mountain";
    }
};

#endif // MOUNTAINS_H
