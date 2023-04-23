#pragma once
#include "object.h"
#include "archer.h"
#include "crossbowman.h"
#include "heavyrider.h"
#include "lightrider.h"
#include "knight.h"
#include "spearman.h"

class objectFabric {
public:
    Archer* createArcher();
    CrossBowMan* createCrossbowman();
    HeavyRider* createHeavyRider();
    LightRider* createLightRider();
    Knight* createKnight();
    SpearMan* createSpearman();
};
