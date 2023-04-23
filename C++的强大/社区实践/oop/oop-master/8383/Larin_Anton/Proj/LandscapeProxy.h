//
// Created by anton on 3/3/20.
//

#ifndef PROJ_LANDSCAPEPROXY_H
#define PROJ_LANDSCAPEPROXY_H

#include "UnitProps.h"
//#include "GameObject.h"

class Mediator;

class LandscapeProxy {
private:
    Mediator *mediator;
public:

    int x;
    int y;


    LandscapeProxy(Mediator *mediator, int x, int y);

    int getGirdle() const;

    int getOrd(UnitDevotion side) const;

    UnitDevotion getColor();
};


#endif //PROJ_LANDSCAPEPROXY_H
