//
// Created by Mila
//

#include "ProxyLandscape.h"

char ProxyLandscape::whatYouName() {
    return landscape->whatYouName();
}

LandscapeInterface *ProxyLandscape::copy() {
    return landscape->copy();
}

void ProxyLandscape::updateUnitHealth(int *healthUnit, char nameUnit) {
    if(!(nameUnit == 'E' && landscape->whatYouName() == '#'))
    {
        landscape->updateUnitHealth(healthUnit, nameUnit);
    }
}

ProxyLandscape::ProxyLandscape(Landscape *landscape) {
    ProxyLandscape::landscape = landscape;

}
