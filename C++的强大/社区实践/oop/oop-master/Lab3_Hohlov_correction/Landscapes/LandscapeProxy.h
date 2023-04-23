
#ifndef UNTITLED13_LANDSCAPEPROXY_H
#define UNTITLED13_LANDSCAPEPROXY_H


#include "Landscape.h"
#include "../Point.h"
#include "../GameField/GameField.h"

class LandscapeProxy {

private:

    Landscape *landscape;

public:

    LandscapeProxy(Landscape *landscape);

    int getDamageFactor(WeaponType type);
    int getAbsorptionFactor(ArmorType type);

};


#endif //UNTITLED13_LANDSCAPEPROXY_H
