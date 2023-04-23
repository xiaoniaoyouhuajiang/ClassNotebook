//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_LANDSCAPE_H
#define GAME_LANDSCAPE_H


#include "../../Units/Unit.h"

class Landscape {
public:
    virtual bool getInformationAboutLandscape() = 0;
    virtual void setBonus(Unit *unit) = 0;
};


#endif //GAME_LANDSCAPE_H
