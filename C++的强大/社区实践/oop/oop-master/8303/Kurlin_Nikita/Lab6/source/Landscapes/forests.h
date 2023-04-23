#ifndef FORESTS_H
#define FORESTS_H
#include "landscape.h"
//#include "Units/unit.h"

class Forest : public Landscape
{
public:

    Forest(){}
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
        return "Forest";
    }
};

#endif // FORESTS_H
