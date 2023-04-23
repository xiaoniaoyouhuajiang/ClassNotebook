//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_MOUNTAINSLANDSCAPE_H
#define GAME_MOUNTAINSLANDSCAPE_H


#include "Landscape.h"

class MountainsLandscape : public Landscape {
    bool getInformationAboutLandscape() override;
    void setBonus(Unit *unit) override;
};


#endif //GAME_MOUNTAINSLANDSCAPE_H
