//
// Created by Alex on 30.03.2020.
//

#ifndef GAME_PROXYLANDSCAPE_H
#define GAME_PROXYLANDSCAPE_H


#include <bits/unique_ptr.h>
#include "Landscape.h"

class ProxyLandscape: public Landscape {
    bool getInformationAboutLandscape() override;

public:
    ProxyLandscape(Landscape *landscape);

    int getBonus(Unit *unit) override;

private:
    Landscape *landscape ;
};


#endif //GAME_PROXYLANDSCAPE_H
