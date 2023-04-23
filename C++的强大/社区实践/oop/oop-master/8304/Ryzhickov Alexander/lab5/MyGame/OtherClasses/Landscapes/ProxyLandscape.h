//
// Created by Alex on 30.03.2020.
//

#ifndef GAME_PROXYLANDSCAPE_H
#define GAME_PROXYLANDSCAPE_H

#include "Landscape.h"

class ProxyLandscape: public Landscape {
    bool getInformationAboutLandscape() override;

public:
    explicit ProxyLandscape(Landscape *landscape);

    void setBonus(Unit *unit) override;

private:
    Landscape *landscape ;
};


#endif //GAME_PROXYLANDSCAPE_H
