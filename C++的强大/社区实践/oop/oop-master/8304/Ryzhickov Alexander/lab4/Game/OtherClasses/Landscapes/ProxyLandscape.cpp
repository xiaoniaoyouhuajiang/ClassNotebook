//
// Created by Alex on 30.03.2020.
//

#include "ProxyLandscape.h"
#include "../../Units/RangedUnits/RangedUnit.h"
#include "../../Units/HeavyInfantry/HeavyInfantry.h"

ProxyLandscape::ProxyLandscape(Landscape *landscape) {
    this->landscape = landscape;
}

bool ProxyLandscape::getInformationAboutLandscape() {
    return landscape->getInformationAboutLandscape();
}

void ProxyLandscape::setBonus(Unit *unit) {
    landscape->setBonus(unit);
}
