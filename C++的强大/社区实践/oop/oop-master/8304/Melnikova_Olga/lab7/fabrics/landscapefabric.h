#pragma once

#include "landscapes/cliff.h"
#include "landscapes/swamp.h"
#include "landscapes/glade.h"
#include "damage.h"

class LandscapeFabric
{
public:
    LandscapeFabric();
    ~LandscapeFabric();
    Glade* glade();
    Swamp* swamp();
    Cliff* cliff();
};


