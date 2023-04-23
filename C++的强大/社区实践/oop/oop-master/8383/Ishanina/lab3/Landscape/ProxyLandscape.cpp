//
// Created by Mila on 18.04.2020.
//

#include "ProxyLandscape.h"

char ProxyLandscape::whatYouName() {
    return landscape->whatYouName();
}

LandscapeInterface *ProxyLandscape::copy() {
    return landscape->copy();
}

void ProxyLandscape::updateUnitHealth(int *healthUnit) {
    landscape->updateUnitHealth(healthUnit);
}

ProxyLandscape::ProxyLandscape(Landscape *landscape) {
    ProxyLandscape::landscape = landscape;

}
