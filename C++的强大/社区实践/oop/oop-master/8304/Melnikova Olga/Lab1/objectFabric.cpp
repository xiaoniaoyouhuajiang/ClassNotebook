#include "objectFabric.h"

Archer* objectFabric::createArcher() {
    Archer* newArcher = new Archer();
    return newArcher;
}
CrossBowMan* objectFabric::createCrossbowman() {
    CrossBowMan* newCrossBowMan = new CrossBowMan();
    return newCrossBowMan;
}
HeavyRider* objectFabric::createHeavyRider() {
    HeavyRider* newHeavyRider = new HeavyRider();
    return newHeavyRider;
}
LightRider* objectFabric::createLightRider() {
    LightRider* newLightRider = new LightRider();
    return newLightRider;
}
Knight* objectFabric::createKnight() {
    Knight* newKnight = new Knight();
    return newKnight;
}
SpearMan* objectFabric::createSpearman() {
    SpearMan* newSpearMan = new SpearMan;
    return newSpearMan;
}
