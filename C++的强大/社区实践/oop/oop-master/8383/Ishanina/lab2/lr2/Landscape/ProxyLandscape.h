//
// Created by Mila
//

#ifndef UNTITLED_PROXYLANDSCAPE_H
#define UNTITLED_PROXYLANDSCAPE_H


#include "Landscape.h"

class ProxyLandscape: public Landscape {
public:
    explicit ProxyLandscape(Landscape* landscape);
    char whatYouName() override;
    LandscapeInterface* copy() override;
    void updateUnitHealth(int* healthUnit, char nameUnit) override;

private:
    Landscape* landscape;

};


#endif //UNTITLED_PROXYLANDSCAPE_H
